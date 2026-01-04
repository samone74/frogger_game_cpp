#include "Lane.h"
#include <cstdlib>

Lane::Lane(int yPosition, int dir, float spd)
    : y(yPosition), direction(dir), speed(spd)
{
}

void Lane::spawnCars(int screenWidth)
{
    cars.clear();

    // Number of cars scales with lane width
    int carCount = screenWidth / 10;

    for (int i = 0; i < carCount; ++i)
    {
        int startX = (i * 10) % screenWidth;
        cars.emplace_back(startX, direction, speed);
    }
}

void Lane::update(float deltaTime, int screenWidth)
{
    // Lazy initialization (spawn once when screen width is known)
    if (cars.empty())
        spawnCars(screenWidth);

    for (auto& car : cars)
        car.update(deltaTime, screenWidth);
}

bool Lane::hasCarAt(int x) const
{
    for (const auto& car : cars)
    {
        if (car.getX() == x)
            return true;
    }
    return false;
}

int Lane::getY() const
{
    return y;
}

const std::vector<Car>& Lane::getCars() const
{
    return cars;
}
