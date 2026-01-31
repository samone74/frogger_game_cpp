#include "game_state_manager.h"

#include "lose_screen.h"
#include "main_game_state.h"
#include "start_screen.h"
#include "win_screen.h"


std::unique_ptr<GameState> GameStateManager::create_state(StateID id, const SdlContext &context) {
    switch (id) {
        case StateID::Play: return std::make_unique<MainGameState>(context);
        case StateID::Start: return std::make_unique<StartScreen>(context);
        case StateID::Lose: return std::make_unique<LoseScreen>(context);
        case StateID::Win: return std::make_unique<WinScreen>(context);
        default: return nullptr;
    }
    return nullptr;
}
