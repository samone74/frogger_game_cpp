#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H
#include <SDL3/SDL.h>
#include "draw_objects.h"
#include <unordered_map>
#include <functional>
class ObjectBase{
  public:
  enum class Type {
    Lanes,
    Car,
    Frog,
    Live
};
    virtual ~ObjectBase(){}
    virtual void update() = 0;
    virtual std::vector<DrawObject> draw() = 0;
    virtual std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() = 0;
    virtual std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() = 0;
    virtual void change_level(int level) = 0;
    virtual Type get_type() const = 0;
    virtual Rectangle get_rect() = 0;
    virtual void set_y(int y) = 0;
  };


#endif //OBJECT_BASE_H
