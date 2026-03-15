#include "draw_object_rect.h"

#include "objects/rectangle.h"

DrawObjectRect::DrawObjectRect(const Rectangle &rectangle, const Color color, const bool fill)
    : color(color.red, color.green, color.blue, color.transparency), fill(fill) {
    rect.x = rectangle.x;
    rect.y = rectangle.y;
    rect.w = rectangle.width;
    rect.h = rectangle.height;
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
