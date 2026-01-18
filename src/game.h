#ifndef GAME_H
#define GAME_H
#include "objects/sdl_context.h"
#include "game_states/game_state_manager.h"

void run_game(SdlContext& ctx);
bool process_transition(GameStateManager& gsm, SdlContext& ctx, const Transition& tr) ;


#endif //GAME_H
