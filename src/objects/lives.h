#ifndef LIVES_H
#define LIVES_H
#include "object_base.h"


class Live :public ObjectBase{
    public:
    explicit Live(int x);
    ~Live() override = default;
    void update() override {};
    std::vector<DrawObject> draw() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override {return {};};
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override {return {};};
    void change_level(int level) override {};
    ObjectBase::Type get_type() const override;
    Rectangle get_rect() override;
    void set_y(int y) override {};
private:
    Rectangle rect{};
    const int height = 5;
    const int width = 5;
    const int m_y = 10;

};



#endif //LIVES_H
