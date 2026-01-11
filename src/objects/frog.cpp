#include "frog.h"
#include <iostream>

Frog::Frog(const int size, const int screen_width, const int screen_height):
size(size), m_screen_width(screen_width), m_screen_height(screen_height), x(screen_width/2), y(screen_height - size) {
}

void Frog::update() {
    if (move_down)
    {y+=speed;}
    if (move_up)
    {y-=speed;}
    if (move_left)
    {x-=speed;}
    if (move_right)
    {x+=speed;}
    // keep in bounds
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (y > m_screen_height - size) y = m_screen_height - size;
    if (x > m_screen_width - size ) x = m_screen_width - size;
}

std::vector<DrawObject> Frog::draw() {
    const Rectangle frog_rectangle(
    x,
    y,
    size,
    size);
    const Color color(0,224,0,255);
    const DrawObject draw_object(color,frog_rectangle, 2);
    return {draw_object};
}

std::unordered_map<SDL_Keycode, std::function<void()>> Frog::get_key_down_map() {
    std::unordered_map<SDL_Keycode, std::function<void()>> key_map = {
            { SDLK_RIGHT, [this]() { start_move_right(); } },
            { SDLK_LEFT, [this]() { start_move_left();  } },
            { SDLK_DOWN, [this]() { start_move_down();  } },
            { SDLK_UP, [this]() { start_move_up();    } }
    };
    return key_map;
}

std::unordered_map<SDL_Keycode, std::function<void()>> Frog::get_key_up_map() {
    std::unordered_map<SDL_Keycode, std::function<void()>> key_map = {
        { SDLK_RIGHT, [this]() { stop_move_right(); } },
        { SDLK_LEFT, [this]() { stop_move_left();  } },
        { SDLK_DOWN, [this]() { stop_move_down();  } },
        { SDLK_UP, [this]() { stop_move_up();    } }
    };
    return key_map;
}

ObjectBase::Type Frog::get_type() const {
    return Type::Frog;
}

Rectangle Frog::get_rect() {
    const Rectangle frog_rectangle(
x,
y,
size,
size);
    return frog_rectangle;
}

void Frog::set_y(int y_in) {
    y = y_in;
}

void Frog::start_move_right() {
    move_right = true;
}
void Frog::start_move_left() {
    move_left = true;
}
void Frog::start_move_down() {
    move_down = true;
}
void Frog::start_move_up() {
    move_up = true;
}
void Frog::stop_move_left() {
    move_left = false;
}
void Frog::stop_move_right() {
    move_right = false;
}
void Frog::stop_move_down() {
    move_down = false;
}
void Frog::stop_move_up() {
    move_up = false;
}