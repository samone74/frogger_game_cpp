#include "draw_object_sprite.h"
#include <SDL3_image/SDL_image.h>

#include <utility>
DrawObjectSprite::DrawObjectSprite(std::string sprite_file, SDL_Renderer *renderer, const Rectangle &rectangle)
    : sprite_file(std::move(sprite_file)) {
    load_texture(renderer);
    rect.x = rectangle.x;
    rect.y = rectangle.y;
    rect.w = rectangle.width;
    rect.h = rectangle.height;

    // Default: use full texture until user sets a frame
    float texW;
    float texH;
    SDL_GetTextureSize(texture, &texW, &texH);
    src_rect = {0, 0, texW, texH};
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
    src_rect = other.src_rect;
    other.texture = nullptr;
}

DrawObjectSprite &DrawObjectSprite::operator=(DrawObjectSprite &&other) noexcept {
    sprite_file = std::move(other.sprite_file);
    texture = other.texture;
    rect.x = other.rect.x;
    rect.y = other.rect.y;
    rect.w = other.rect.w;
    rect.h = other.rect.h;
    src_rect = other.src_rect;
    other.texture = nullptr;
    return *this;
}

void DrawObjectSprite::draw(SDL_Renderer *renderer) {
    if (modified) {
        load_texture(renderer);
        modified = false;
    }
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // SDL_RenderFillRect(renderer, &rect);
    SDL_RenderTexture(renderer, texture, &src_rect, &rect);
}
// NOLINTNEXTLINE(readability-identifier-length)
void DrawObjectSprite::set_position(const Position &position) {
    rect.x = position.x;
    rect.y = position.y;
}

std::pair<float, float> DrawObjectSprite::get_position() { return {rect.x, rect.y}; }

void DrawObjectSprite::set_source_rect(const SDL_FRect &src) { src_rect = src; }