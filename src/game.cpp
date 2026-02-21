#include "game.h"

MainGame::MainGame(int width, int height) :m_ctx(GAME_NAME, 800, 600){
}

MainGame::~MainGame() = default;

void MainGame::run_game() {
    m_gsm.change_state(StateID::Start, m_ctx);
    bool running = true;
    SDL_Event e;
    while (running) {

        // --- Handle events ---
        while (SDL_PollEvent(&e)) {
            if (auto tr = m_gsm.get()->handle_event(m_ctx, e)) {
                running = process_transition(*tr);
            }
        }

        // --- Update ---
        if (auto tr = m_gsm.get()->update(m_ctx)) {
            running = process_transition(*tr);
        }

        // --- Render ---
        SDL_SetRenderDrawColor(m_ctx.renderer(), 0, 125, 0, 255);
        SDL_RenderClear(m_ctx.renderer());
        m_gsm.get()->render(m_ctx);
        SDL_RenderPresent(m_ctx.renderer());
        SDL_Delay(16); // ~60 FPS
    }
}

bool MainGame::process_transition(const Transition &tr) {
    switch (tr.type) {
        case Transition::Type::Switch:
            m_gsm.change_state(tr.target, m_ctx);
        return true;
        case Transition::Type::Quit:
            return false;
    }
    return true;
}
