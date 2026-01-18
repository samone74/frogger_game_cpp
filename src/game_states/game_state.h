#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <SDL3/SDL_events.h>
#include "Transition.h"

class SdlContext;

class GameState {
public:
    virtual ~GameState() = default;

    // Called once when the state becomes active
    virtual void on_enter(SdlContext& ctx){};

    // Called once right before the state is replaced
    virtual void on_exit(SdlContext& ctx){};

    // Input/events for the state
    virtual TransitionRequest handle_event(const SdlContext& ctx, const SDL_Event& e) = 0;

    virtual TransitionRequest update(const SdlContext& ctx) = 0;

    // Render the state
    virtual void render(const SdlContext& ctx) = 0;
};


#endif //GAME_STATE_H
