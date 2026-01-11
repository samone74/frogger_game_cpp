#include "count_down_timer.h"
#include <utility>

CountDownTimer::CountDownTimer(const std::function<void(const std::string& )>& call_back_function, Uint32 time_left):
m_call_back_function(call_back_function), m_time_left(time_left * 1000) {
    last_time_tick =  SDL_GetTicks();
    m_call_back_function("Time left: " + std::to_string(m_time_left / 1000));
}

void CountDownTimer::start() {
    last_time_tick = SDL_GetTicks();
}

void CountDownTimer::update() {
    const Uint32 now = SDL_GetTicks();
    const Uint32 delta_time = now - last_time_tick;
    if ( delta_time > 1000) {
        m_time_left -= delta_time;
        last_time_tick = now;
        m_call_back_function("Time left: " + std::to_string(m_time_left / 1000));
    }
}