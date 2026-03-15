#include "start_screen.h"

#include "objects/draw_objects/draw_object_text.h"
#include "objects/sdl_context.h"

StartScreen::StartScreen(const SdlContext &ctx) {
    std::string font_file = "assets/fonts/arial.ttf";
    std::string text = "Press any key to continue";
    objects.push_back(std::make_unique<TextDrawObject>(ctx.renderer(), text, font_file, font_size, RED, m_x, m_y));
}

TransitionRequest StartScreen::handle_event(const SdlContext &ctx, const SDL_Event &event) {
    switch (event.type) {
    case (SDL_EVENT_QUIT): {
        return Transition::quit();
    }
    case (SDL_EVENT_KEY_DOWN): {
        if (event.key.key == SDLK_ESCAPE) {
            return Transition::quit();
        }
        return Transition::switch_to(StateID::Play);
    }
    default: {
        return std::nullopt;
    }
    }
}

void StartScreen::render(SdlContext &ctx) {
    for (const auto &object : objects) {
        object->draw(ctx.renderer());
    }
}