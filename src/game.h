#ifndef GAME_H
#define GAME_H
#include "objects/sdl_context.h"
#include "game_states/game_state_manager.h"

void run_game(SdlContext& ctx);
bool process_transition(GameStateManager& gsm, SdlContext& ctx, const Transition& tr) ;

class MainGame {
    public:
    MainGame(int width, int height);
    ~MainGame();
    void run_game();
private:
    const std::string m_game_name = "frogger";
    SdlContext m_ctx;
    GameStateManager m_gsm;
    bool process_transition(const Transition& tr);
};


#endif //GAME_H
