#include "lives.h"

Live::Live(const int x){
    rect = Rectangle(x, m_y, width, height);
}

std::vector<DrawObject> Live::draw() {
    DrawObject obj(Color(255,0,0,255), rect, 3);
    return {obj};
}

ObjectBase::Type Live::get_type() const {
    return Type::Live;
}

Rectangle Live::get_rect() {
    return rect;
}




