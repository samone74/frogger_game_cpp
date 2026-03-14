#ifndef DRAW_OBJECT_RECT_H
#define DRAW_OBJECT_RECT_H

#include <utility>

#include "../color.h"
#include "SDL3/SDL.h"
#include "draw_object_base.h"

class DrawObjectRect : public DrawObjectBase {
  public:
    // NOLINTNEXTLINE(readability-identifier-length)
    DrawObjectRect(float x, float y, float w, float h, Color color, bool fill);
    ~DrawObjectRect() override = default;
    void draw(SDL_Renderer *renderer) override;
    // NOLINTNEXTLINE(readability-identifier-length)
    void set_position(float x, float y) override;
    std::pair<float, float> get_position() override;

  private:
    SDL_Color color{};
    bool fill;
    SDL_FRect rect{0, 0, 0, 0};
};

#endif // DRAW_OBJECT_RECT_H
