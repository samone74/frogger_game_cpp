#ifndef LANES_H
#define LANES_H
#include <memory>

#include "object_base.h"


class Lanes:public ObjectBase {
  public:
    Lanes(int screen_width, int screen_height);
    ~Lanes() override = default;
    void update() override {};
    std::vector<DrawObjectBase*> get_draw_objects() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override {return {};}
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override {return {};}
    void change_level(int level) override;
    [[nodiscard]] Type get_type() const override;
    void set_y(float y) override{};
  Rectangle get_rect() override;
    private:
      int m_number_of_lanes = 1;
      const int m_screen_width, m_screen_height;
      float m_lane_size;
    const float line_size = 2;
    const int max_number_of_lanes = 10;
  std::vector<std::unique_ptr<DrawObjectBase>> m_draw_objects;
  void create_draw_objects();
};



#endif //LANES_H
