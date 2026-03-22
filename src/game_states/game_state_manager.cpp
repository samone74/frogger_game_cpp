#include "game_state_manager.h"

#include "lose_screen.h"
#include "main_game_state.h"
#include "start_screen.h"
#include "text_to_screen_state.h"
#include "win_screen.h"

std::unique_ptr<GameState> GameStateManager::create_state(StateID identifier, const SdlContext &context) {
    const std::string font_file = "assets/fonts/arial.ttf";
    constexpr int font_size = 16;
    constexpr Position position(10, 10);
    std::unordered_map<SDL_Keycode, StateID> key_map;
    key_map.insert(std::pair(SDLK_P, StateID::Play));
    const std::string start_text = "Press P to start";
    switch (identifier) {
    case StateID::Play:
        return std::make_unique<MainGameState>(context);
    case StateID::Start:
        return std::make_unique<TextToScreenState>(context, start_text, font_size, RED, font_file, position, key_map);
    case StateID::Lose:
        return std::make_unique<LoseScreen>(context);
    case StateID::Win:
        return std::make_unique<WinScreen>(context);
    default:
        return nullptr;
    }
}
