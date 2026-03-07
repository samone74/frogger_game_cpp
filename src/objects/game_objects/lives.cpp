#include "lives.h"

#include "objects/draw_objects/draw_object_rect.h"

Live::Live(const float x): m_x(x){
    create_draw_objects() ;
}

std::vector<DrawObjectBase *> Live::get_draw_objects() {
    std::vector<DrawObjectBase *> draw_objects_ptr;
    for (auto& draw_object : m_draw_objects) {
        draw_objects_ptr.push_back(draw_object.get());
    }
    return draw_objects_ptr;
}

ObjectBase::Type Live::get_type() const {
    return Type::Live;
}

Rectangle Live::get_rect() {
    return Rectangle(m_x, m_y, width, height);
}

void Live::create_draw_objects() {
    m_draw_objects.clear();
    m_draw_objects.push_back(std::make_unique<DrawObjectRect>(m_x, m_y, width, height, RED, true ));
}




