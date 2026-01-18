#include "game.h"


void run_game(SdlContext& ctx) {
    GameStateManager gsm;
    gsm.change_state(StateID::Play, ctx);

    bool running = true;
    SDL_Event e;

    while (running) {

        // --- Handle events ---
        while (SDL_PollEvent(&e)) {
            if (auto tr = gsm.get()->handle_event(ctx, e)) {
                running = process_transition(gsm, ctx, *tr);
            }
        }

        // --- Update ---
        if (auto tr = gsm.get()->update(ctx)) {
            running = process_transition(gsm, ctx, *tr);
        }

        // --- Render ---
        SDL_SetRenderDrawColor(ctx.renderer(), 0, 125, 0, 255);
        SDL_RenderClear(ctx.renderer());
        gsm.get()->render(ctx);
        SDL_RenderPresent(ctx.renderer());
        SDL_Delay(16); // ~60 FPS
    }
}

bool process_transition(GameStateManager& gsm, SdlContext& ctx, const Transition& tr) {
    switch (tr.type) {
        case Transition::Type::Switch:
            gsm.change_state(tr.target, ctx);
        return true;

        case Transition::Type::Quit:
            return false;
    }
    return true;
}

