#ifndef CAR_H
#define CAR_H
#include <memory>

#include "object_base.h"
#include "objects/color.h"

class Car final : public ObjectBase {
    public:
    Car(float x, float y, float speed, Color color, float width, float height, int screen_width, int screen_height);
    ~Car() override = default;
    void update() override;
    std::vector<DrawObjectBase*> get_draw_objects() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override {return {};}
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override {return {};}
    void change_level(int level) override {};
    [[nodiscard]] Type get_type() const override;
    void set_y(float y) override{};
    Rectangle get_rect() override;
private:
    float m_x, m_y;
    const float m_width, m_height;
    const int m_screen_width, m_screen_height;
    float m_speed;
    const Color m_color;
    std::vector<std::unique_ptr<DrawObjectBase>> m_draw_objects;
    void create_car_draw_objects();
    void move_draw_objects(float dx) const;
};



#endif //CAR_H
