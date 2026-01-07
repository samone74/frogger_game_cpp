#include "lanes.h"

Lanes::Lanes(const int screen_width, const int screen_height): m_screen_width(screen_width),
                                                               m_screen_height(screen_height) {
  m_lane_size = m_screen_height / (max_number_of_lanes + 2);
}

std::vector<DrawObject> Lanes::draw() {
  std::vector<DrawObject> objects;
  const Rectangle lanes_rectangle(
    0,
    m_screen_height / 2 - m_lane_size / 2 * m_number_of_lanes,
    m_screen_width,
    m_lane_size * m_number_of_lanes);
  const Color color(123, 123, 123, 255);
  const DrawObject draw_object(color, lanes_rectangle, 0);
  objects.push_back(draw_object);
  const Color color_white(255, 255, 255, 255);

  for (int i = 0; i < m_number_of_lanes + 1; i++) {
    const Rectangle lanes_lines_rectangle(
      0,
      m_screen_height / 2 - m_lane_size / 2 * m_number_of_lanes + m_lane_size * (i)- line_size / 2,
      m_screen_width,
      line_size);
    objects.push_back({color_white, lanes_lines_rectangle, 1});
  }

  return {objects};
}

void Lanes::change_level(const int level) {
  m_number_of_lanes = level;
}

ObjectBase::Type Lanes::get_type() const {
  return Type::Lanes;
}

Rectangle Lanes::get_rect() {
  const Rectangle lanes_rectangle(
  0,
  m_lane_size,
  m_screen_width,
  m_lane_size * m_number_of_lanes);
  return lanes_rectangle;
}
