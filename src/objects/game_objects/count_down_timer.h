#ifndef COUNT_DOWN_TIMER_H
#define COUNT_DOWN_TIMER_H
#include <functional>
#include <string>
#include <SDL3/SDL.h>

class CountDownTimer {
    public:
    CountDownTimer(const std::function<void(const std::string&)>& call_back_function, Uint32 time_left);
    ~CountDownTimer() = default;
    void start();
    void update();
    private:
    const std::function<void(const std::string&)> m_call_back_function;
    Uint32  last_time_tick;
    Uint32  m_time_left;
};



#endif //COUNT_DOWN_TIMER_H
