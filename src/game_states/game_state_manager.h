#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <memory>
#include "game_state.h"
#include "transition.h"
#include "objects/sdl_context.h"

class GameStateManager {
public:
    GameStateManager() = default;

    void change_state(StateID id, SdlContext& ctx) {
        if (current) {
            current->on_exit(ctx);
        }
        current = create_state(id, ctx);
        current->on_enter(ctx);
    }

    GameState* get() { return current.get(); }

private:
    std::unique_ptr<GameState> current;

    std::unique_ptr<GameState> create_state(StateID id, const SdlContext& context);
};



#endif
