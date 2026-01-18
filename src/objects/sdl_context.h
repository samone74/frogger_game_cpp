#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H

#include <SDL3/SDL.h>
#include <string>

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

private:
    void cleanup() noexcept;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    int m_width;
    int m_height;
};
#endif //SDL_CONTEXT_H
