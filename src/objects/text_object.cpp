#include "text_object.h"

TextObject::TextObject(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const std::string& text,
    SDL_Color color,
    float x,
    float y
)
    : m_renderer(renderer),
      m_font(font),
      m_color(color),
      m_text(text)
{
    rebuild_texture();
    set_position(x, y);
}

TextObject::~TextObject()
{
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
    }
}

TextObject::TextObject(TextObject&& other) noexcept
{
    *this = std::move(other);
}

TextObject& TextObject::operator=(TextObject&& other) noexcept
{
    if (this != &other) {
        SDL_DestroyTexture(m_texture);

        m_renderer = other.m_renderer;
        m_font = other.m_font;
        m_color = other.m_color;
        m_text = std::move(other.m_text);
        m_texture = other.m_texture;
        m_rect = other.m_rect;

        other.m_texture = nullptr;
    }
    return *this;
}

void TextObject::set_position(float x, float y)
{
    m_rect.x = x;
    m_rect.y = y;
}

void TextObject::set_text(const std::string& text)
{
    if (m_text == text)
        return;
    m_text = text;
    rebuild_texture();
}

SDL_Texture* TextObject::get_texture() const
{
    return m_texture;
}

const SDL_FRect& TextObject::get_rect() const
{
    return m_rect;
}

void TextObject::rebuild_texture()
{
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(
        m_font,
        m_text.c_str(),
        0,
        m_color
    );


    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    m_rect.w = static_cast<float>(surface->w);
    m_rect.h = static_cast<float>(surface->h);

    SDL_DestroySurface(surface);
}
