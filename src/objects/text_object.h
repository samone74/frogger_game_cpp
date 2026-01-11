
#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include <string>
#include "SDL3/SDL.h"
#include <SDL3_ttf/SDL_ttf.h>


class TextObject {
public:
    TextObject(
        SDL_Renderer* renderer,
        TTF_Font* font,
        const std::string& text,
        SDL_Color color,
        float x,
        float y
    );

    ~TextObject();

    // non-copyable
    TextObject(const TextObject&) = delete;
    TextObject& operator=(const TextObject&) = delete;

    // movable
    TextObject(TextObject&& other) noexcept;
    TextObject& operator=(TextObject&& other) noexcept;

    void set_position(float x, float y);
    void set_text(const std::string& text);

    SDL_Texture* get_texture() const;
    const SDL_FRect& get_rect() const;

private:
    void rebuild_texture();

    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    SDL_Color m_color;

    std::string m_text;
    SDL_Texture* m_texture = nullptr;
    SDL_FRect m_rect {0, 0, 0, 0};
};


#endif //TEXT_OBJECT_H
