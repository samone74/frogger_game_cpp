#include "game_state_manager.h"

#include "create_game_states.h"
#include "main_game_state.h"
#include "text_to_screen_state.h"

std::unique_ptr<GameState> GameStateManager::create_state(StateID identifier, const SdlContext &context) {

    switch (identifier) {
    case StateID::Play:
        return std::make_unique<MainGameState>(context);
    case StateID::Start:
        return create_start_screen_state(context);
    case StateID::Lose:
        return create_lose_screen_state(context);
    case StateID::Win:
        return create_win_screen_state(context);
    default:
        return nullptr;
    }
}
