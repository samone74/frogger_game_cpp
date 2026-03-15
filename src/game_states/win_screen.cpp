#include "win_screen.h"
#include "objects/sdl_context.h"

WinScreen::WinScreen(const SdlContext &ctx) {
    std::string font_file = "assets/fonts/arial.ttf";
    std::string text = "You won, press P to start again";
    objects.push_back(std::make_unique<TextDrawObject>(ctx.renderer(), text, RED, m_x, m_y, font_file, font_size));
}

TransitionRequest WinScreen::handle_event(const SdlContext &ctx, const SDL_Event &event) {
    switch (event.type) {
    case (SDL_EVENT_QUIT): {
        return Transition::quit();
    }
    case (SDL_EVENT_KEY_DOWN): {
        if (event.key.key == SDLK_ESCAPE) {
            return Transition::quit();
        }
        if (event.key.key == SDLK_P) {
            return Transition::switch_to(StateID::Play);
        }
    }
    default: {
        return std::nullopt;
    }
    }
}

void WinScreen::render(SdlContext &ctx) {
    for (const auto &object : objects) {
        object->draw(ctx.renderer());
    }
}