#include "game.h"

#include "objects/color.h"
#include "objects/screen_size.h"

MainGame::MainGame(const ScreenSize &screen_size) : m_ctx(GAME_NAME, screen_size) {}

MainGame::~MainGame() = default;

void MainGame::run_game() {
    m_gsm.change_state(StateID::Start, m_ctx);
    bool running = true;
    SDL_Event events;
    while (running) {
        // --- Handle events ---
        while (SDL_PollEvent(&events)) {
            if (auto transition_request = m_gsm.get()->handle_event(m_ctx, events)) {
                running = process_transition(*transition_request);
            }
        }

        // --- Update ---
        if (auto tr = m_gsm.get()->update(m_ctx)) {
            running = process_transition(*tr);
        }

        // --- Render ---
        SDL_SetRenderDrawColor(m_ctx.renderer(), GREEN.red, GREEN.green, GREEN.blue, GREEN.transparency);
        SDL_RenderClear(m_ctx.renderer());
        m_gsm.get()->render(m_ctx);
        SDL_RenderPresent(m_ctx.renderer());
        SDL_Delay(1 / fps * SECONDS_TO_MILLISECONDS); // ~60 FPS
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
