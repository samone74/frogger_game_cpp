#include "sdl_context.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <stdexcept>
#include <utility>

SdlContext::SdlContext(const std::string &title, const ScreenSize &screen_size) : m_screen_size(screen_size) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }

    m_window = SDL_CreateWindow(title.c_str(), screen_size.width, screen_size.height, 0);
    if (!m_window) {
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }
    TTF_Init();
}

SdlContext::~SdlContext() { cleanup(); }

SdlContext::SdlContext(SdlContext &&other) noexcept : m_screen_size(other.m_screen_size) { *this = std::move(other); }

SdlContext &SdlContext::operator=(SdlContext &&other) noexcept {
    if (this != &other) {
        cleanup();
        m_screen_size = other.m_screen_size;
        m_window = other.m_window;
        m_renderer = other.m_renderer;
        other.m_window = nullptr;
        other.m_renderer = nullptr;
    }
    return *this;
}

void SdlContext::draw_object_to_screen(const std::vector<DrawObjectBase *> &draw_objects) const {
    for (const auto &draw_object : draw_objects) {
        draw_object->draw(m_renderer);
    }
}

void SdlContext::cleanup() noexcept {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}
