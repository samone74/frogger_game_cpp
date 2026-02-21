#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "game_state.h"
#include <vector>
#include <memory>
#include "objects/draw_objects.h"
#include "objects/object_base.h"

class StartScreen:public GameState {
    public:
    explicit StartScreen(const SdlContext& ctx);
    ~StartScreen() override = default;
    // Called once when the state becomes active
    void on_enter(SdlContext& ctx) override{};

    // Called once right before the state is replaced
    void on_exit(SdlContext& ctx) override{};

    // Input/events for the state
    TransitionRequest handle_event(const SdlContext& ctx, const SDL_Event& event) override;

    TransitionRequest update(const SdlContext& ctx) override {return std::nullopt;;};

    // Render the state
    void render(SdlContext& ctx) override;

private:
    std::vector<std::unique_ptr<ObjectBase>> objects;
    std::vector<TextDrawObject> text_objects;
};



#endif //START_SCREEN_H
