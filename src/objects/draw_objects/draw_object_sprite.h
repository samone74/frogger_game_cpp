#ifndef DRAW_OBJECT_SPRITE_H
#define DRAW_OBJECT_SPRITE_H
#include "SDL3/SDL.h"
#include "draw_object_base.h"
#include <string>

class DrawObjectSprite final : public DrawObjectBase {
  public:
    DrawObjectSprite(std::string sprite_file, SDL_Renderer *renderer, const Rectangle &rectangle);

    ~DrawObjectSprite() override = default;

    DrawObjectSprite(const DrawObjectSprite &) = delete;

    DrawObjectSprite &operator=(const DrawObjectSprite &) = delete;

    DrawObjectSprite(DrawObjectSprite &&other) noexcept;

    DrawObjectSprite &operator=(DrawObjectSprite &&other) noexcept;

    void draw(SDL_Renderer *renderer) override;
    // NOLINTNEXTLINE(readability-identifier-length)
    void set_position(const Position &position) override;

    std::pair<float, float> get_position() override;

    void set_source_rect(const SDL_FRect &src) override;

  private:
    std::string sprite_file;
    SDL_Texture *texture = nullptr;
    SDL_FRect rect{0, 0, 0, 0};
    SDL_FRect src_rect{0.0, 0, 0, 0};
    bool modified = false;
    void load_texture(SDL_Renderer *renderer);
};

#endif // DRAW_OBJECT_SPRITE_H
