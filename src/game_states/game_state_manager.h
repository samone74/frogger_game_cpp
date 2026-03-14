#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "game_state.h"
#include "objects/sdl_context.h"
#include "transition.h"
#include <memory>

class GameStateManager {
  public:
    GameStateManager() = default;

    void change_state(StateID identifier, SdlContext &ctx) {
        if (current) {
            current->on_exit(ctx);
        }
        current = create_state(identifier, ctx);
        current->on_enter(ctx);
    }

    GameState *get() { return current.get(); }

  private:
    std::unique_ptr<GameState> current;

    static std::unique_ptr<GameState> create_state(StateID identifier, const SdlContext &context);
};

#endif
