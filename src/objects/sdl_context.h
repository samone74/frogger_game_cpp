#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H
#include "draw_objects/draw_object_base.h"
#include "screen_size.h"
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class SdlContext {
  public:
    SdlContext(const std::string &title, const ScreenSize &screen_size);
    ~SdlContext();

    // Non-copyable
    SdlContext(const SdlContext &) = delete;
    SdlContext &operator=(const SdlContext &) = delete;

    // Movable
    SdlContext(SdlContext &&other) noexcept;
    SdlContext &operator=(SdlContext &&other) noexcept;

    [[nodiscard]] SDL_Window *window() const noexcept { return m_window; }
    [[nodiscard]] SDL_Renderer *renderer() const noexcept { return m_renderer; }

    [[nodiscard]] int width() const noexcept { return m_screen_size.width; }
    [[nodiscard]] int height() const noexcept { return m_screen_size.height; }

    void draw_object_to_screen(const std::vector<DrawObjectBase *> &draw_objects) const;

  private:
    void cleanup() noexcept;
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    ScreenSize m_screen_size;
};
#endif // SDL_CONTEXT_H
