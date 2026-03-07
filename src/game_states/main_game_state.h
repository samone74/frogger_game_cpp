#ifndef MAIN_GAME_STATE_H
#define MAIN_GAME_STATE_H
#include "game_state.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include "objects/rectangle.h"
#include "objects/game_objects/object_base.h"


class MainGameState final :public GameState {
    public:
    explicit MainGameState(const SdlContext& ctx);
    ~MainGameState() override = default;
    TransitionRequest handle_event(const SdlContext& ctx, const SDL_Event& event) override;
    TransitionRequest update(const SdlContext& ctx) override;
    void render(SdlContext& ctx) override;
private:
    std::vector<std::unique_ptr<ObjectBase>> objects;
    int m_level = 1;
    int m_lives = 5;
    std::unordered_map<SDL_Keycode, std::function<void()> > m_key_down_events;
    std::unordered_map<SDL_Keycode, std::function<void()> > m_key_up_events;
    void create_cars(const SdlContext& ctx);
    void set_level() const;
    void change_level(const SdlContext& ctx, int level_increase);

    void create_live_objects();
    void remove_live_objects();
};
bool detect_collision(const Rectangle& a, const Rectangle& b);


#endif //MAIN_GAME_STATE_H
