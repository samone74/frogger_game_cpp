#include "game_state_manager.h"

#include "main_game_state.h"
#include "start_screen.h"


std::unique_ptr<GameState> GameStateManager::create_state(StateID id, const SdlContext &context) {
    switch (id) {
        case StateID::Play: return std::make_unique<MainGameState>(context);
        case StateID::Start: return std::make_unique<StartScreen>(context);
        default: return nullptr;
    }
    return nullptr;
}
