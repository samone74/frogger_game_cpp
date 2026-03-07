#include "car.h"

#include "objects/draw_objects/draw_object_rect.h"

Car::Car(const float x, const float y, const float speed, const Color color,
         const float width, const float height, const int screen_width, const int screen_height): m_x(x), m_y(y), m_width(width), m_height(height),
                                                                            m_screen_width(screen_width), m_screen_height(screen_height),
                                                                            m_speed(speed)
                                                                            , m_color(color) {
    create_car_draw_objects();
}

void Car::update() {
    m_x += m_speed;
    //check on screen location.
    if (m_x > static_cast<float>( m_screen_width)) {
        m_x = 0 - m_width;
    }
    if (m_x < -m_width) {
        m_x = static_cast<float>( m_screen_width - 1);
    }
    create_car_draw_objects();
}

std::vector<DrawObjectBase *> Car::get_draw_objects() {
    std::vector<DrawObjectBase *> draw_objects_ptr;
    for (auto& draw_object : m_draw_objects) {
        draw_objects_ptr.push_back(draw_object.get());
    }
    return draw_objects_ptr;
}

ObjectBase::Type Car::get_type() const {
    return Type::Car;
}

Rectangle Car::get_rect() {
    return Rectangle(m_x, m_y, m_width, m_height);
}

void Car::create_car_draw_objects() {
    m_draw_objects.clear();
    Color black(0, 0, 0, 255);
    // complete car rectangle
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(m_x, m_y, m_width, m_height, m_color, true));
    // front rectangle
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(m_x, m_y, m_width / 4, m_height, black, false));
    // middle rectangle
    m_draw_objects.push_back(
        std::make_unique<DrawObjectRect>(m_x + m_width / 4, m_y, m_width / 2, m_height, black, false));
    // back rectangle
    m_draw_objects.push_back(
        std::make_unique<DrawObjectRect>(m_x + 3 * m_width / 4, m_y, m_width / 4, m_height, black, false));
}

void Car::move_draw_objects(const float dx) const {
    for (auto &ptr : m_draw_objects) { ptr->set_position(ptr->get_position().first + dx, m_y); }
}
