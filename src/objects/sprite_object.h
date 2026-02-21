#ifndef SPRIT_OBJECT_H
#define SPRIT_OBJECT_H
#include <string>
#include <SDL3/SDL_render.h>

#include "draw_object_base.h"


class SpriteObject {
public:
    SpriteObject(const std::string &sprite_file, SDL_Renderer *renderer, float x,
                 float y, float width, float height);

    ~SpriteObject() = default;

    // non-copyable
    SpriteObject(const SpriteObject &) = delete;

    SpriteObject &operator=(const SpriteObject &) = delete;

    // movable
    SpriteObject(SpriteObject &&other) noexcept;

    SpriteObject &operator=(SpriteObject &&other) noexcept;

    SDL_Texture *get_texture() const;

    const SDL_FRect &get_rect() const;

private:
    std::string sprite_file;
    SDL_Texture *texture = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    SDL_FRect m_rect{0, 0, 0, 0};
    SDL_Texture* load_texture();
};

class SpriteDrawObject: public DrawObjectBase {
    public:
    SpriteDrawObject(const std::string &sprite_file, SDL_Renderer *renderer);
    ~SpriteDrawObject() override = default;
    SpriteDrawObject(const SpriteDrawObject &) = delete;
    SpriteDrawObject &operator=(const SpriteDrawObject &) = delete;
    SpriteDrawObject(SpriteDrawObject &&other) noexcept;
    SpriteDrawObject &operator=(SpriteDrawObject &&other) noexcept;
    void draw(SDL_Renderer *renderer) override;
private:
    std::string sprite_file;
    SDL_Texture *texture = nullptr;
    SDL_FRect rect{0, 0, 0, 0};
    SDL_Texture* load_texture(SDL_Renderer *renderer) const;
};

#endif //SPRIT_OBJECT_H
