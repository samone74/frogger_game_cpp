#ifndef LIVES_H
#define LIVES_H
#include <memory>

#include "object_base.h"


class Live :public ObjectBase{
    public:
    explicit Live(float x);
    ~Live() override = default;
    void update() override {};
    std::vector<DrawObjectBase*> get_draw_objects() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override {return {};};
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override {return {};};
    void change_level(int level) override {};
    [[nodiscard]] Type get_type() const override;
    void set_y(float y) override {};
    Rectangle get_rect() override;
private:
    const float height = 5;
    const float width = 5;
    const float m_y = 10;
    float m_x = 10;
    std::vector<std::unique_ptr<DrawObjectBase>> m_draw_objects;
    void create_draw_objects();
};



#endif //LIVES_H
