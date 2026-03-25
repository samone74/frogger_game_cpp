#include "create_game_states.h"

std::unique_ptr<TextToScreenState> create_start_screen_state(const SdlContext &context) {
    const std::string font_file = "assets/fonts/arial.ttf";
    constexpr int font_size = 16;
    constexpr Position position(10, 10);
    std::unordered_map<SDL_Keycode, StateID> key_map;
    key_map.insert(std::pair(SDLK_P, StateID::Play));
    const std::string start_text = "Press P to start";
    return std::make_unique<TextToScreenState>(context, start_text, font_size, RED, font_file, position, key_map);
}
std::unique_ptr<TextToScreenState> create_win_screen_state(const SdlContext &context) {
    const std::string font_file = "assets/fonts/arial.ttf";
    constexpr int font_size = 16;
    constexpr Position position(10, 10);
    std::unordered_map<SDL_Keycode, StateID> key_map;
    key_map.insert(std::pair(SDLK_P, StateID::Play));
    const std::string start_text = "You won. Press P to restart";
    return std::make_unique<TextToScreenState>(context, start_text, font_size, RED, font_file, position, key_map);
}

std::unique_ptr<TextToScreenState> create_lose_screen_state(const SdlContext &context) {
    const std::string font_file = "assets/fonts/arial.ttf";
    constexpr int font_size = 16;
    constexpr Position position(10, 10);
    std::unordered_map<SDL_Keycode, StateID> key_map;
    key_map.insert(std::pair(SDLK_P, StateID::Play));
    const std::string start_text = "You lost. Press P to restart";
    return std::make_unique<TextToScreenState>(context, start_text, font_size, RED, font_file, position, key_map);
}
