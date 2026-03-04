#include "lose_screen.h"
#include "objects/sdl_context.h"

LoseScreen::LoseScreen(const SdlContext &ctx) {
    std::string font_file = "assets/fonts/arial.ttf";
    std::string text = "You lost, press P to try again";
    objects.push_back(std::make_unique<TextDrawObject>(ctx.renderer(), text, font_file, 20, RED, 10, 10));
}

TransitionRequest LoseScreen::handle_event(const SdlContext &ctx, const SDL_Event &event) {
    if (event.type == SDL_EVENT_QUIT)
        return Transition::quit() ;
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_P)
        return Transition::switch_to(StateID::Play);
    }
    return std::nullopt;
}

void LoseScreen::render(SdlContext& ctx) {
    for (auto &object: objects) {
        object->draw(ctx.renderer());
    }
}