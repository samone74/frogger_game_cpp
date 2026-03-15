#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H
#include "objects/draw_objects/draw_object_base.h"
#include <SDL3/SDL.h>
#include <cstdint>
#include <functional>
#include <unordered_map>

#include "objects/rectangle.h"

class ObjectBase {
  public:
    enum Type : std::uint8_t { Lanes, Car, Frog, Live, Night, Timer };
    virtual ~ObjectBase() = default;
    virtual void update() = 0;
    virtual std::vector<DrawObjectBase *> get_draw_objects() = 0;
    virtual std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() = 0;
    virtual std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() = 0;
    virtual void change_level(int level) = 0;
    [[nodiscard]] virtual Type get_type() const = 0;
    // NOLINTNEXTLINE(readability-identifier-length)
    virtual void set_y(float y) = 0;
    virtual Rectangle get_rect() = 0;
};

#endif // OBJECT_BASE_H
