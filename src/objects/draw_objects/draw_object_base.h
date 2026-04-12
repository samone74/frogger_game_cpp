#ifndef DRAW_OBJECT_BASE_H
#define DRAW_OBJECT_BASE_H
#include "objects/rectangle.h"
#include <SDL3/SDL_render.h>
#include <utility>
/* Interface class for draw objects.
 *
 */
class DrawObjectBase {
  public:
    DrawObjectBase() = default;
    virtual ~DrawObjectBase() = default;
    DrawObjectBase(const DrawObjectBase &) = delete;
    DrawObjectBase(DrawObjectBase &&) = delete;
    DrawObjectBase &operator=(const DrawObjectBase &) = delete;
    virtual void draw(SDL_Renderer *m_renderer) = 0;
    virtual void set_position(const Position &position) = 0; // NOLINT(readability-identifier-length)
    virtual std::pair<float, float> get_position() = 0;
    virtual void set_source_rect(const SDL_FRect &rect) = 0;
};

#endif // DRAW_OBJECT_BASE_H
