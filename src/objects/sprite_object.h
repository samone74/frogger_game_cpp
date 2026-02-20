#ifndef SPRIT_OBJECT_H
#define SPRIT_OBJECT_H
#include <string>
#include <SDL3/SDL_render.h>


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


#endif //SPRIT_OBJECT_H
