#include "car.h"

#include "objects/draw_objects/draw_object_rect.h"

Car::Car(const int x, const int y, const int speed, const Color color,
         int width, int height, int screen_width, int screen_height): m_x(x), m_y(y), m_speed(speed), m_color(color),
                                                                      m_width(width), m_height(height),
                                                                      m_screen_width(screen_width)
                                                                      , m_screen_height(screen_height) {
    create_car_draw_objects();
}

void Car::update() {
    m_x += m_speed;
    //check on screen location.
    if (m_x > m_screen_width) {
        m_x = 0 - m_width;
    }
    if (m_x < -m_width) {
        m_x = m_screen_width - 1;
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

void Car::move_draw_objects(float dx)
{
    for (auto &ptr : m_draw_objects) { ptr->set_position(ptr->get_position().first + dx, m_y); }
}

Rectangle Car::get_rect() {
    return Rectangle(m_x, m_y, m_width, m_height);
}
