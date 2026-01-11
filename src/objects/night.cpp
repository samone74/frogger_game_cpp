#include "night.h"

Night::Night(const int screen_width, const int screen_height) : rect(0, 0, screen_width, screen_height), color(0,0,0,0) {
}

std::vector<DrawObject> Night::draw() {
    std::vector<DrawObject> objects;
    objects.push_back({color, rect, 5, true});
    return objects;

}

ObjectBase::Type Night::get_type() const {
    return ObjectBase::Type::Night;
}

Rectangle Night::get_rect() {
    return rect;
}


