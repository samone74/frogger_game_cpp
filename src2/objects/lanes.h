#ifndef LANES_H
#define LANES_H
#include "object_base.h"


class Lanes:public ObjectBase {
  public:
    Lanes(int screen_width, int screen_height);
    ~Lanes() override = default;
    void update() override {};
    std::vector<DrawObject> draw() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override {return {};}
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override {return {};}
    void change_level(int level) override;
    Type get_type() const override;
    Rectangle get_rect() override;
    void set_y(int y) override{};
    private:
      int m_number_of_lanes = 10;
      const int m_screen_width, m_screen_height;
      int m_lane_size;
    const int line_size = 2;
};



#endif //LANES_H
