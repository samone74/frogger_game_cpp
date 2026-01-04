#ifndef LANE_H
#define LANE_H


#include <vector>
#include "Car.h"

class Lane
{
public:
    Lane(int yPosition, int direction, float speed);

    void update(float deltaTime, int screenWidth);

    // Collision query
    bool hasCarAt(int x) const;

    // Accessors
    int getY() const;
    const std::vector<Car>& getCars() const;

private:
    int y;
    int direction;
    float speed;

    std::vector<Car> cars;

    void spawnCars(int screenWidth);
};


#endif //LANE_H
