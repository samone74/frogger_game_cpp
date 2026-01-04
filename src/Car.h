#ifndef CAR_H
#define CAR_H


class Car
{
public:
    Car(int startX, int direction, float speed);

    // Update car position using delta time
    void update(float deltaTime, int screenWidth);

    int getX() const;
    int getDirection() const;

private:
    float x;          // float for smooth movement
    int direction;    // -1 = left, +1 = right
    float speed;      // units per second
};


#endif //CAR_H
