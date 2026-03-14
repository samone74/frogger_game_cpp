#include "draw_object_rect.h"

// NOLINTNEXTLINE(readability-identifier-length)
DrawObjectRect::DrawObjectRect(const float x, const float y, const float width, const float height, const Color color,
                               const bool fill)
    : color(color.red, color.green, color.blue, color.transparency), fill(fill) {
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
}

void DrawObjectRect::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (fill) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderRect(renderer, &rect);
    }
}

void DrawObjectRect::set_position(const float x, const float y) { // NOLINT(readability-identifier-length)
    rect.x = x;
    rect.y = y;
}

std::pair<float, float> DrawObjectRect::get_position() { return {rect.x, rect.y}; }
