#ifndef DRAW_OBJECT_BASE_H
#define DRAW_OBJECT_BASE_H
#include <SDL3/SDL_render.h>


class DrawObjectBase {
public:
    virtual ~DrawObjectBase() = delete;
    DrawObjectBase(const DrawObjectBase&) = delete;
    DrawObjectBase(DrawObjectBase&&) = delete;
    DrawObjectBase& operator=(const DrawObjectBase&) = delete;
    virtual void draw(SDL_Renderer* m_renderer) = 0;
};

#endif //DRAW_OBJECT_BASE_H
