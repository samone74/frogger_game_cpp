#include "draw_object_sprite.h"
#include <SDL3_image/SDL_image.h>

DrawObjectSprite::DrawObjectSprite(const std::string &sprite_file, SDL_Renderer *renderer, const float x, const float y,
                                   const float width, const float height): sprite_file(sprite_file) {
    load_texture(renderer);
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
}


void DrawObjectSprite::load_texture(SDL_Renderer *renderer) {
    SDL_Surface *surf = IMG_Load(sprite_file.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);
}


DrawObjectSprite::DrawObjectSprite(DrawObjectSprite &&other) noexcept {
    sprite_file = std::move(other.sprite_file);
    texture = other.texture;
    rect.x = other.rect.x;
    rect.y = other.rect.y;
    rect.w = other.rect.w;
    rect.h = other.rect.h;
    other.texture = nullptr;
}

DrawObjectSprite & DrawObjectSprite::operator=(DrawObjectSprite &&other) noexcept {
    sprite_file = std::move(other.sprite_file);
    texture = other.texture;
    rect.x = other.rect.x;
    rect.y = other.rect.y;
    rect.w = other.rect.w;
    rect.h = other.rect.h;
    other.texture = nullptr;
    return *this;
}

void DrawObjectSprite::draw(SDL_Renderer *renderer) {
    if (modified) { load_texture(renderer); }
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}

void DrawObjectSprite::set_position(const float x, const float y) {
    rect.x = x;
    rect.y = y;
}

std::pair<float, float> DrawObjectSprite::get_position() {
    return {rect.x,rect.y};
}