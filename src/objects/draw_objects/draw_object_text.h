#ifndef DRAW_OBJECT_TEXT_H
#define DRAW_OBJECT_TEXT_H
#include <string>
#include "SDL3/SDL.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "draw_object_base.h"
#include "objects/color.h"

class TextDrawObject final : public DrawObjectBase {
public:
    TextDrawObject(SDL_Renderer* renderer,
        const std::string& text,
        const std::string& font_file,
        float font_size,
        Color color,
        float x,
        float y);
    ~TextDrawObject() override = default;
    TextDrawObject(const TextDrawObject&) = delete;
    TextDrawObject& operator=(const TextDrawObject&) = delete;
    TextDrawObject(TextDrawObject&& other) noexcept;
    TextDrawObject& operator=(TextDrawObject&& other) noexcept;
    void draw(SDL_Renderer *renderer) override;
    void set_text(const std::string& text_new);
    void set_position(float x, float y) override;
    std::pair<float, float> get_position() override;
private:
    void rebuild_texture(SDL_Renderer *renderer);
    bool modified = false;
    TTF_Font* font = nullptr;
    SDL_Color color{};
    std::string text;
    SDL_Texture* texture = nullptr;
    SDL_FRect rect {0, 0, 0, 0};
};
#endif //DRAW_OBJECT_TEXT_H
