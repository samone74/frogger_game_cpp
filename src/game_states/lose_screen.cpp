#include "lose_screen.h"
#include "objects/sdl_context.h"

LoseScreen::LoseScreen(const SdlContext &ctx) {
    text_objects.push_back({TextID::Start,"You lost, press P to try again", 20, ctx.height()/2, {255,0,0,0},0});

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
    for (auto &text_object: text_objects) {
        ctx.draw_text_to_screen(text_object);
    }
}