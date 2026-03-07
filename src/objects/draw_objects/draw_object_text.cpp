#include "draw_object_text.h"
#include <iostream>

TextDrawObject::TextDrawObject(SDL_Renderer *renderer, const std::string &text, const std::string &font_file,
                               const float font_size, const Color color, const float x, const float y) : color(
    color.red, color.green, color.blue, color.transparency) , text(text){
    font = TTF_OpenFont(font_file.c_str(), font_size);
    if (!font) {
        std::string error = SDL_GetError();
        std::cout << "TTF_OpenFont error: " << SDL_GetError() << "\n";
    }
    rebuild_texture(renderer);
    set_position(x,y);
}

TextDrawObject::TextDrawObject(TextDrawObject &&other) noexcept {
    color = other.color;
    font = other.font;
    texture = other.texture;
    rect = other.rect;
    other.font = nullptr;
    other.texture = nullptr;
}

TextDrawObject & TextDrawObject::operator=(TextDrawObject &&other) noexcept {
    if (this != &other) {
        color = other.color;
        font = other.font;
        texture = other.texture;
        rect = other.rect;
        other.font = nullptr;
        other.texture = nullptr;
    }
    return *this;
}

void TextDrawObject::draw(SDL_Renderer *renderer) {
    if (modified) {
        rebuild_texture(renderer);
        modified = false;
    }
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}

void TextDrawObject::set_text(const std::string &text_new) {
    text = text_new;
    modified = true;
}

void TextDrawObject::set_position(float x, float y) {
    rect.x = x;
    rect.y = y;
}

std::pair<float, float> TextDrawObject::get_position() {
    return {rect.x, rect.y};
}

Rectangle TextDrawObject::get_rect() const {
    return {rect.x, rect.y, rect.w, rect.h};
}

void TextDrawObject::rebuild_texture(SDL_Renderer *renderer) {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    SDL_Surface *surface = TTF_RenderText_Blended(
        font,
        text.c_str(),
        0,
        color
    );
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = static_cast<float>(surface->w);
    rect.h = static_cast<float>(surface->h);
    SDL_DestroySurface(surface);
}


