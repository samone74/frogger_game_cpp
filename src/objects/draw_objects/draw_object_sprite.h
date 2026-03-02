#ifndef DRAW_OBJECT_SPRITE_H
#define DRAW_OBJECT_SPRITE_H
#include <string>
#include "SDL3/SDL.h"
#include "draw_object_base.h"

class DrawObjectSprite final : public DrawObjectBase {
public:
    DrawObjectSprite(const std::string &sprite_file,  SDL_Renderer* renderer, float x, float y, float width, float height);

    ~DrawObjectSprite() override = default;

    DrawObjectSprite(const DrawObjectSprite &) = delete;

    DrawObjectSprite &operator=(const DrawObjectSprite &) = delete;

    DrawObjectSprite(DrawObjectSprite &&other) noexcept;

    DrawObjectSprite &operator=(DrawObjectSprite &&other) noexcept;

    void draw(SDL_Renderer *renderer) override;

    void set_position(float x, float y) override;

    std::pair<float, float> get_position() override;

private:
    std::string sprite_file;
    SDL_Texture *texture = nullptr;
    SDL_FRect rect{0, 0, 0, 0};
    bool modified = false;
    void load_texture(SDL_Renderer *renderer);
};



#endif //DRAW_OBJECT_SPRITE_H
