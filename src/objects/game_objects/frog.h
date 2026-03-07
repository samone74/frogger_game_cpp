#ifndef FROG_H
#define FROG_H
#include <memory>

#include "objects/sdl_context.h"
#include "objects/game_objects/object_base.h"


class Frog: public ObjectBase {
  public:
    Frog(int size, const SdlContext& context);
    ~Frog() override = default;
    void update() override;
    std::vector<DrawObjectBase*> get_draw_objects() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override;
    void change_level(int level) override;
    Type get_type() const override;
    void set_y(int y_in) override;
    void start_move_right();
    void start_move_left();
    void start_move_up();
    void start_move_down();
    void stop_move_left();
    void stop_move_right();
    void stop_move_up();
    void stop_move_down();
    Rectangle get_rect() override;
private:
    int x, y;
    const int size;
    const int m_screen_width, m_screen_height;
    const int speed = 5;
    bool move_right = false;
    bool move_left = false;
    bool move_up = false;
    bool move_down = false;
    std::vector<std::unique_ptr<DrawObjectBase>> m_draw_objects;
    void create_draw_objects( const SdlContext& context);
};

#endif //FROG_H
