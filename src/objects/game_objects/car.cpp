#include "car.h"

#include "objects/draw_objects/draw_object_rect.h"

Car::Car(const Rectangle &rectangle, const float speed, const Color color, const ScreenSize &screen_size)
    : m_rectangle(rectangle), m_screen_width(screen_size.width), m_screen_height(screen_size.height), m_speed(speed),
      m_color(color) {
    create_car_draw_objects();
}

void Car::update() {
    m_rectangle.x += m_speed;
    // check on screen location.
    if (m_rectangle.x > static_cast<float>(m_screen_width)) {
        m_rectangle.x = 0 - m_rectangle.width;
    }
    if (m_rectangle.x < -m_rectangle.width) {
        m_rectangle.x = static_cast<float>(m_screen_width - 1);
    }
    create_car_draw_objects();
}

std::vector<DrawObjectBase *> Car::get_draw_objects() {
    std::vector<DrawObjectBase *> draw_objects_ptr;
    draw_objects_ptr.reserve(m_draw_objects.size());
    for (auto &draw_object : m_draw_objects) {
        draw_objects_ptr.push_back(draw_object.get());
    }
    return draw_objects_ptr;
}

ObjectBase::Type Car::get_type() const { return Type::Car; }

Rectangle Car::get_rect() { return m_rectangle; }

void Car::create_car_draw_objects() {
    m_draw_objects.clear();
    // complete car rectangle
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(m_rectangle.x, m_rectangle.y, m_rectangle.width,
                                                              m_rectangle.height, m_color, true));
    // front rectangle
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(m_rectangle.x, m_rectangle.y, m_rectangle.width / 4,
                                                              m_rectangle.height, BLACK, false));
    // middle rectangle
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(m_rectangle.x + m_rectangle.width / 4, m_rectangle.y,
                                                              m_rectangle.width / 2, m_rectangle.height, BLACK, false));
    // back rectangle
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(m_rectangle.x + 3 * m_rectangle.width / 4, m_rectangle.y,
                                                              m_rectangle.width / 4, m_rectangle.height, BLACK, false));
}

void Car::move_draw_objects(const float d_x) const {
    for (const auto &draw_object : m_draw_objects) {
        draw_object->set_position(draw_object->get_position().first + d_x, m_rectangle.y);
    }
}
