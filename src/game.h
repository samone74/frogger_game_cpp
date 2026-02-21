#ifndef GAME_H
#define GAME_H
#include "objects/sdl_context.h"
#include "game_states/game_state_manager.h"

class MainGame {
    public:
    MainGame(int width, int height);
    ~MainGame();
    void run_game();
private:
    static constexpr const char* GAME_NAME = "frogger";    SdlContext m_ctx;
    GameStateManager m_gsm;
    bool process_transition(const Transition& tr);
};


#endif //GAME_H
