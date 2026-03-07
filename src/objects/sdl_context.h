#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include "draw_objects/draw_object_base.h"

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

    [[nodiscard]] int width() const noexcept { return window_width; }
    [[nodiscard]] int height() const noexcept { return window_height; }

    void draw_object_to_screen(const std::vector<DrawObjectBase*>& draw_objects) const;

private:
    void cleanup() noexcept;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    int window_width;
    int window_height;
};
#endif //SDL_CONTEXT_H
