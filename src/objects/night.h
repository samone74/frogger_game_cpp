#ifndef NIGHT_H
#define NIGHT_H

#include "object_base.h"

class Night:public ObjectBase{
    public:
    Night(int screen_width, int screen_height);
    ~Night() = default;
    void update() override {};
    std::vector<DrawObject> draw() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override {return {};};
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override {return {};};
    void change_level(int level) override {};
    Type get_type() const override;
    Rectangle get_rect() override;
    void set_y(int y) override {};
private:
    const Rectangle rect;
    const Color color;
};



#endif //NIGHT_H
