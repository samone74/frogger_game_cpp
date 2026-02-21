#include "sprite_object.h"
#include <SDL3_image/SDL_image.h>
SpriteObject::SpriteObject(const std::string &sprite_file, SDL_Renderer *renderer, const float x, const float y, const float width,
    const float height) : sprite_file(sprite_file), m_renderer(renderer), m_rect(x, y, width, height) {
    //load image
    texture = load_texture();
}

SDL_Texture * SpriteObject::get_texture() const {
    return texture;
}

const SDL_FRect & SpriteObject::get_rect() const {
    return m_rect;
}

SDL_Texture* SpriteObject::load_texture() {
    SDL_Surface* surf = IMG_Load(sprite_file.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surf);
    SDL_DestroySurface(surf);
    return tex;
}

SpriteDrawObject::SpriteDrawObject(const std::string &sprite_file,  SDL_Renderer* renderer): sprite_file(sprite_file) {
    texture = load_texture(renderer);
}

void SpriteDrawObject::draw(SDL_Renderer *renderer) {
    SDL_RenderTexture(renderer(), texture, nullptr, &rect);
}

SDL_Texture* SpriteDrawObject::load_texture(SDL_Renderer *renderer) const {
    SDL_Surface* surf = IMG_Load(sprite_file.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);
    return tex;
}
