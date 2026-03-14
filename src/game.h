#ifndef GAME_H
#define GAME_H
#include "game_states/game_state_manager.h"
#include "objects/screen_size.h"
#include "objects/sdl_context.h"

constexpr int SECONDS_TO_MILLISECONDS = 1000;

class MainGame {
  public:
    explicit MainGame(const ScreenSize &screen_size);

    ~MainGame();

    void run_game();

  private:
    static constexpr const char *GAME_NAME = "frogger";
    SdlContext m_ctx;
    GameStateManager m_gsm;
    const int fps = 60;

    bool process_transition(const Transition &transition_request);
};

#endif // GAME_H
