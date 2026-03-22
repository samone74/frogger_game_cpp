#include "text_to_screen_state.h"
#include "objects/sdl_context.h"

TextToScreenState::TextToScreenState(const SdlContext &ctx, const std::string &text, const int font_size,
                                     const Color font_color, const std::string &font_file, const Position position,
                                     const std::unordered_map<SDL_Keycode, StateID> &m_key_map)
    : font_size(font_size), m_x(position.x), m_y(position.y), m_key_map(m_key_map) {
    objects.push_back(
        std::make_unique<TextDrawObject>(ctx.renderer(), text, font_color, m_x, m_y, font_file, font_size));
}

TransitionRequest TextToScreenState::handle_event(const SdlContext &ctx, const SDL_Event &event) {
    switch (event.type) {
    case (SDL_EVENT_QUIT): {
        return Transition::quit();
    }
    case (SDL_EVENT_KEY_DOWN): {
        if (event.key.key == SDLK_ESCAPE) {
            return Transition::quit();
        }
        if (m_key_map.contains(event.key.key)) {
            return Transition::switch_to(m_key_map.at(event.key.key));
        }
    }
    default: {
        return std::nullopt;
    }
    }
}

void TextToScreenState::render(SdlContext &ctx) {
    for (const auto &object : objects) {
        object->draw(ctx.renderer());
    }
}
