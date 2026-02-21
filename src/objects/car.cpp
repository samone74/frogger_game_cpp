#include "car.h"

Car::Car(const int x, const int y, const int speed, const Color color,
    int width, int height, int screen_width, int screen_height):
m_x(x),m_y(y), m_speed(speed), m_color(color),m_width(width), m_height(height), m_screen_width(screen_width)
, m_screen_height(screen_height){}

void Car::update() {
    m_x += m_speed;
    //check on screen location.
    if (m_x > m_screen_width) {
        m_x = 0 - m_width;
    }
    if (m_x < -m_width) {
        m_x = m_screen_width - 1;
    }
}

std::vector<DrawObject> Car::draw() {
    const Rectangle car_rectangle(
  m_x,
  m_y,
  m_width,
  m_height);
    Color color(0,0,0,255);
    Rectangle front_rectangle(car_rectangle.x, car_rectangle.y, car_rectangle.width/4,car_rectangle.height);
    Rectangle middle_rectangle(car_rectangle.x + car_rectangle.width/4, car_rectangle.y, car_rectangle.width/2,car_rectangle.height);
    Rectangle back_rectangle(car_rectangle.x + 3 * car_rectangle.width/4, car_rectangle.y, car_rectangle.width/4,car_rectangle.height);
    DrawObject draw_object(m_color, car_rectangle, 2);
    DrawObject draw_object2(color, front_rectangle, 2, false);
    DrawObject draw_object3(color, middle_rectangle, 2, false);
    DrawObject draw_object4(color, back_rectangle, 2, false);

    // === HEADLIGHTS ===
    /*
    const int light_length = m_width * 2;
    const int light_height = m_height / 2;
    const int light_y = m_y + m_height / 4;

    Color light_color(255, 255, 255, 200); // transparent white

    Rectangle light_rect(
        m_speed > 0 ? m_x + m_width : m_x - light_length,
        light_y,
        light_length,
        light_height
    );

    DrawObject light(light_color, light_rect, 3, true);*/

    return {draw_object, draw_object2, draw_object3, draw_object4};
}

ObjectBase::Type Car::get_type() const {
    return Type::Car;
}

Rectangle Car::get_rect() {
    const Rectangle car_rectangle(
m_x,
m_y,
m_width,
m_height);
    return car_rectangle;
}
