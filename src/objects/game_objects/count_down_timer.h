#ifndef COUNT_DOWN_TIMER_H
#define COUNT_DOWN_TIMER_H
#include <functional>
#include <memory>
#include <SDL3/SDL.h>

#include "object_base.h"
#include "objects/sdl_context.h"
#include "objects/draw_objects/draw_object_text.h"

class CountDownTimer:public ObjectBase {
    public:
    CountDownTimer(const SdlContext &context, Uint32 time_left);
    ~CountDownTimer() override = default;
    void start();
    void update() override;

    std::vector<DrawObjectBase*> get_draw_objects() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_down_map() override;
    std::unordered_map<SDL_Keycode, std::function<void()>> get_key_up_map() override;
    void change_level(int level) override;
    [[nodiscard]] Type get_type() const override;
    void set_y(float y) override;
    Rectangle get_rect() override;

    private:
    Uint32  last_time_tick;
    Uint32  m_time_left;
    std::unique_ptr<TextDrawObject> m_draw_object = nullptr;
    float m_y;
};



#endif //COUNT_DOWN_TIMER_H
