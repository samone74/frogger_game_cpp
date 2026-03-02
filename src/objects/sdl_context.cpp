#include "sdl_context.h"
#include <iostream>
#include <stdexcept>
#include <utility>

SdlContext::SdlContext(const std::string& title, const int width, const int height)
    : window_width(width), window_height(height)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }

    m_window = SDL_CreateWindow(title.c_str(), window_width, window_height, 0);
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
    font = TTF_OpenFont("C:/Users/samzw/OneDrive/Documenten/GitHub/frogger_game_cpp/cmake-build-debug/desktop/assets/arial.ttf", 32);
    if (!font) {
        std::string error = SDL_GetError();
        std::cout << "TTF_OpenFont error: " << SDL_GetError() << "\n";
    }
}

SdlContext::~SdlContext() {
    cleanup();
}

SdlContext::SdlContext(SdlContext&& other) noexcept: window_width(other.window_width), window_height(other.window_height) {
    *this = std::move(other);
}

SdlContext& SdlContext::operator=(SdlContext&& other) noexcept {
    if (this != &other) {
        cleanup();
        window_height = other.window_height;
        window_width = other.window_width;
        m_window = other.m_window;
        m_renderer = other.m_renderer;
        font = other.font;
        other.m_window = nullptr;
        other.m_renderer = nullptr;
    }
    return *this;
}


void SdlContext::draw_object_to_screen(const std::vector<DrawObjectBase *> &draw_objects) {
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
