#ifndef RECTANGLE_H
#define RECTANGLE_H

struct Rectangle {
    float x;
    float y;
    float width;
    float height;
};

struct Position {
    // NOLINTNEXTLINE(readability-identifier-length)
    float x = 0.0;
    // NOLINTNEXTLINE(readability-identifier-length)
    float y = 0.0;
    float rotation_angle = 0.0;
};

#endif // RECTANGLE_H
