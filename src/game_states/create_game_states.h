#ifndef FROGGER_CREATE_GAME_STATES_H
#define FROGGER_CREATE_GAME_STATES_H
#include "text_to_screen_state.h"

#include <memory>

std::unique_ptr<TextToScreenState> create_start_screen_state(const SdlContext &context);
std::unique_ptr<TextToScreenState> create_win_screen_state(const SdlContext &context);
std::unique_ptr<TextToScreenState> create_lose_screen_state(const SdlContext &context);

#endif // FROGGER_CREATE_GAME_STATES_H
