#include "draw_object_rect.h"

DrawObjectRect::DrawObjectRect(const float x, const float y, const float w, const float h,
                               const Color color,
                               const bool fill) : color(
        {static_cast<Uint8>(color.red), static_cast<Uint8>(color.green),
         static_cast<Uint8>(color.blue), static_cast<Uint8>(color.transparency)}),
                                                  fill(fill) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void DrawObjectRect::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (fill) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderRect(renderer, &rect);
    }
}

void DrawObjectRect::set_position(float x, float y) {
    rect.x = x;
    rect.y = y;
}

std::pair<float, float> DrawObjectRect::get_position() {
    return {rect.x, rect.y};
}
