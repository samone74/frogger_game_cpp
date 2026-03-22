
#ifndef FROGGER_TEXT_TO_SCREEN_STATE_H
#define FROGGER_TEXT_TO_SCREEN_STATE_H
#include "game_state.h"
#include "objects/color.h"
#include "objects/draw_objects/draw_object_text.h"
#include "objects/rectangle.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class TextToScreenState final : public GameState {
  public:
    TextToScreenState(const SdlContext &ctx, const std::string &text, int font_size, Color font_color,
                      const std::string &font_file, Position position,
                      const std::unordered_map<SDL_Keycode, StateID> &m_key_map);
    ~TextToScreenState() override = default;
    // Called once when the state becomes active
    void on_enter(SdlContext &ctx) override {};

    // Called once right before the state is replaced
    void on_exit(SdlContext &ctx) override {};

    // Input/events for the state
    TransitionRequest handle_event(const SdlContext &ctx, const SDL_Event &event) override;

    TransitionRequest update(const SdlContext &ctx) override { return std::nullopt; };

    // Render the state
    void render(SdlContext &ctx) override;

  private:
    std::vector<std::unique_ptr<TextDrawObject>> objects;
    const int font_size;
    const float m_x;
    const float m_y;
    std::unordered_map<SDL_Keycode, StateID> m_key_map;
};

#endif // FROGGER_TEXT_TO_SCREEN_STATE_H
