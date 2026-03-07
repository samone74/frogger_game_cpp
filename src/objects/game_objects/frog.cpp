#include "frog.h"
#include "objects/draw_objects/draw_object_rect.h"
#include "objects/draw_objects/draw_object_sprite.h"

Frog::Frog(const float size,  const SdlContext& context):
x(static_cast<float>(context.width())/2), y(static_cast<float>(context.height()) - size), size(size), m_screen_width(context.width()), m_screen_height(context.height()) {
    create_draw_objects(context);
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
    if (y > static_cast<float>(m_screen_height) - size) y = static_cast<float>(m_screen_height) - size;
    if (x > static_cast<float>(m_screen_width) - size ) x = static_cast<float>(m_screen_width) - size;
    m_draw_objects.at(0)->set_position(x, y);
}

std::vector<DrawObjectBase *> Frog::get_draw_objects() {
    std::vector<DrawObjectBase *> draw_objects_ptr;
    for (auto& draw_object : m_draw_objects) {
        draw_objects_ptr.push_back(draw_object.get());
    }
    return draw_objects_ptr;
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

void Frog::change_level(int level) {
    move_down = false;
    move_up = false;
    move_left = false;
    move_right = false;
}

ObjectBase::Type Frog::get_type() const {
    return Type::Frog;
}


void Frog::set_y(const float y_in) {
    y = y_in;
    move_down = false;
    move_up = false;
    move_left = false;
    move_right = false;
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

void Frog::create_draw_objects( const SdlContext& context) {
    m_draw_objects.clear();
    ;
   // m_draw_objects.push_back(std::make_unique<DrawObjectRect>(x, y, size, size, FROGGREEN, true));
    const std::string sprite_file = "assets\\sprites\\frog2.png";
    m_draw_objects.push_back(std::make_unique<DrawObjectSprite>(sprite_file, context.renderer(),x, y, size, size ));
}

void Frog::stop_move_up() {
    move_up = false;
}

Rectangle Frog::get_rect() {
    return Rectangle(x, y, size, size);
}
