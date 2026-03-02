#include "lanes.h"

#include "objects/color.h"
#include "objects/draw_objects/draw_object_rect.h"

Lanes::Lanes(const int screen_width, const int screen_height): m_screen_width(screen_width),
                                                               m_screen_height(screen_height) {
  m_lane_size = m_screen_height / (max_number_of_lanes + 2);
  create_draw_objects();
}

std::vector<DrawObjectBase *> Lanes::get_draw_objects() {
  std::vector<DrawObjectBase *> draw_objects_ptr;
  for (auto& draw_object : m_draw_objects) {
    draw_objects_ptr.push_back(draw_object.get());
  }
  return draw_objects_ptr;
}

void Lanes::change_level(const int level) {
  m_number_of_lanes = level;
}

ObjectBase::Type Lanes::get_type() const {
  return Type::Lanes;
}

void Lanes::create_draw_objects() {
  m_draw_objects.clear();
  const Color gray(123, 123, 123, 255);
  const Color white(255, 255, 255, 255);
  m_draw_objects.push_back(std::make_unique<DrawObjectRect>(0,  m_screen_height / 2 - m_lane_size / 2 * m_number_of_lanes,
    m_screen_width,
    m_lane_size * m_number_of_lanes, gray, false ));
  for (int i = 0; i < m_number_of_lanes + 1; i++) {
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(  0,
      m_screen_height / 2 - m_lane_size / 2 * m_number_of_lanes + m_lane_size * (i)- line_size / 2,
      m_screen_width,
      line_size, white, true));
  }
}

Rectangle Lanes::get_rect() {
  return Rectangle(0, m_screen_height / 2 - m_lane_size / 2 * m_number_of_lanes, line_size);
}

