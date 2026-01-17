#include "sdl_context.h"
#include <stdexcept>
#include <utility>

SdlContext::SdlContext(const std::string& title, const int width, const int height)
    : m_width(width), m_height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    m_window = SDL_CreateWindow(title.c_str(), m_width, m_height, 0);
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
}

SdlContext::~SdlContext() {
    cleanup();
}

SdlContext::SdlContext(SdlContext&& other) noexcept: m_width(other.m_width), m_height(other.m_height) {
    *this = std::move(other);
}

SdlContext& SdlContext::operator=(SdlContext&& other) noexcept {
    if (this != &other) {
        cleanup();
        m_height = other.m_height;
        m_width = other.m_width;
        m_window = other.m_window;
        m_renderer = other.m_renderer;
        other.m_window = nullptr;
        other.m_renderer = nullptr;
    }
    return *this;
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
