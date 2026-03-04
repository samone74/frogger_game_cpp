#include "start_screen.h"

#include "objects/sdl_context.h"
#include "objects/draw_objects/draw_object_text.h"

StartScreen::StartScreen(const SdlContext &ctx) {
    std::string font_file = "assets/fonts/arial.ttf";
    std::string text = "Press any key to continue";
    objects.push_back(std::make_unique<TextDrawObject>(ctx.renderer(), text, font_file, 20, RED, 10, 10));
}

TransitionRequest StartScreen::handle_event(const SdlContext &ctx, const SDL_Event &event) {
    if (event.type == SDL_EVENT_QUIT)
        return Transition::quit() ;
    if (event.type == SDL_EVENT_KEY_DOWN) {
        return Transition::switch_to(StateID::Play);
    }
    return std::nullopt;
}

void StartScreen::render(SdlContext& ctx) {
    for (auto &object: objects) {
        object->draw(ctx.renderer());
    }
}