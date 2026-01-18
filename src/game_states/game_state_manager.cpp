#include "game_state_manager.h"

#include "main_game_state.h"


std::unique_ptr<GameState> GameStateManager::create_state(StateID id, const SdlContext &context) {
    switch (id) {
        case StateID::Play: return std::make_unique<MainGameState>(context);
    }
    return nullptr;
}
