#include "sprite_object.h"

SpriteObject::SpriteObject(const std::string &sprite_file, SDL_Renderer *renderer, const float x, const float y, const float width,
    const float height) : sprite_file(sprite_file), m_renderer(renderer), m_rect(x, y, width, height) {
    //load image
}

SDL_Texture * SpriteObject::get_texture() const {
    return texture;
}

const SDL_FRect & SpriteObject::get_rect() const {
    return m_rect;
}
