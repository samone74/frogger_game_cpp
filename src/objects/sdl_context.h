#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include "draw_objects.h"
#include "text_object.h"
#include <unordered_map>
#include <memory>

class SdlContext {
public:
    SdlContext(const std::string& title, int width, int height);
    ~SdlContext();

    // Non-copyable
    SdlContext(const SdlContext&) = delete;
    SdlContext& operator=(const SdlContext&) = delete;

    // Movable
    SdlContext(SdlContext&& other) noexcept;
    SdlContext& operator=(SdlContext&& other) noexcept;

    [[nodiscard]] SDL_Window* window() const noexcept { return m_window; }
    [[nodiscard]] SDL_Renderer* renderer() const noexcept { return m_renderer; }

    [[nodiscard]] int width() const noexcept { return m_width; }
    [[nodiscard]] int height() const noexcept { return m_height; }
    void draw_object_to_screen(const DrawObject &draw_object) const;
    void draw_text_to_screen(const TextDrawObject &text_object);
private:
    void cleanup() noexcept;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    TTF_Font *font = nullptr;
    int m_width;
    int m_height;
    std::unordered_map<TextID, std::unique_ptr<TextObject>> m_textCache;

};
#endif //SDL_CONTEXT_H
