#include "count_down_timer.h"

#include "game.h"
#include "objects/sdl_context.h"

CountDownTimer::CountDownTimer(const SdlContext &context, const Uint32 time_left)
    : m_time_left(time_left * SECONDS_TO_MILLISECONDS) {
    last_time_tick = SDL_GetTicks();
    std::string font_file = "assets/fonts/arial.ttf";
    constexpr float font_size = 18;
    Color font_color = WHITE;
    constexpr float m_x = 50;
    m_y = 0;
    m_draw_object = std::make_unique<TextDrawObject>(
        context.renderer(), "Time left: " + std::to_string(m_time_left / SECONDS_TO_MILLISECONDS), font_color, m_x, m_y,
        font_file, font_size);
}

void CountDownTimer::start() { last_time_tick = SDL_GetTicks(); }

void CountDownTimer::update() {
    const Uint32 now = SDL_GetTicks();
    const Uint32 delta_time = now - last_time_tick;
    if (delta_time > SECONDS_TO_MILLISECONDS) {
        m_time_left -= delta_time;
        last_time_tick = now;
        m_draw_object->set_text("Time left: " + std::to_string(m_time_left / SECONDS_TO_MILLISECONDS));
    }
}

std::vector<DrawObjectBase *> CountDownTimer::get_draw_objects() { return {m_draw_object.get()}; }

std::unordered_map<SDL_Keycode, std::function<void()>> CountDownTimer::get_key_down_map() { return {}; }

std::unordered_map<SDL_Keycode, std::function<void()>> CountDownTimer::get_key_up_map() { return {}; }

void CountDownTimer::change_level(int level) {}

ObjectBase::Type CountDownTimer::get_type() const { return Type::Timer; }

void CountDownTimer::set_y(float y) { m_y = y; } // NOLINT(readability-identifier-length)

Rectangle CountDownTimer::get_rect() { return m_draw_object->get_rect(); }
