#ifndef LOSE_SCREEN_H
#define LOSE_SCREEN_H

#include "game_state.h"
#include "objects/draw_objects/draw_object_text.h"
#include <memory>
#include <vector>

class LoseScreen final : public GameState {
  public:
    explicit LoseScreen(const SdlContext &ctx);

    ~LoseScreen() override = default;

    // Called once when the state becomes active
    void on_enter(SdlContext &ctx) override {};

    // Called once right before the state is replaced
    void on_exit(SdlContext &ctx) override {};

    // Input/events for the state
    TransitionRequest handle_event(const SdlContext &ctx, const SDL_Event &event) override;

    TransitionRequest update(const SdlContext &ctx) override {
        return std::nullopt;
        ;
    };

    // Render the state
    void render(SdlContext &ctx) override;

  private:
    std::vector<std::unique_ptr<TextDrawObject>> objects;
    const int font_size = 20;
    const int m_x = 10;
    const int m_y = 10;
};

#endif // LOSE_SCREEN_H
