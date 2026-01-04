#ifndef FROG_H
#define FROG_H
#include "objects/object_base.h"


class Frog: public ObjectBase {
  public:
    Frog(int size, int screen_width, int screen_height );
    ~Frog() override = default;
    void update() override;
    std::vector<DrawObject> draw() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override;
    void change_level(int level) override {};
    Type get_type() const override;
    Rectangle get_rect() override;
    void set_y(int y_in) override;
    void start_move_right();
    void start_move_left();
    void start_move_up();
    void start_move_down();
    void stop_move_left();
    void stop_move_right();
    void stop_move_up();
    void stop_move_down();
private:
    int x, y;
    const int size;
    const int m_screen_width, m_screen_height;
    const int speed = 5;
    bool move_right = false;
    bool move_left = false;
    bool move_up = false;
    bool move_down = false;
};

#endif //FROG_H
