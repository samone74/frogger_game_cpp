#include "Car.h"

Car::Car(int startX, int dir, float spd)
    : x(static_cast<float>(startX)), direction(dir), speed(spd)
{
}

void Car::update(float deltaTime, int screenWidth)
{
    x += direction * speed * deltaTime;

    // Wrap around screen
    if (x >= screenWidth)
        x = 0.0f;
    else if (x < 0.0f)
        x = static_cast<float>(screenWidth - 1);
}

int Car::getX() const
{
    return static_cast<int>(x);
}

int Car::getDirection() const
{
    return direction;
}
