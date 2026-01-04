#include "Frog.h"

Frog::Frog(int startX, int startY)
    : x(startX), y(startY), screenWidth(0), screenHeight(0)
{
}

void Frog::setBounds(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
}

void Frog::moveUp()
{
    if (y > 0)
        y--;
}

void Frog::moveDown()
{
    if (screenHeight == 0 || y < screenHeight - 1)
        y++;
}

void Frog::moveLeft()
{
    if (x > 0)
        x--;
}

void Frog::moveRight()
{
    if (screenWidth == 0 || x < screenWidth - 1)
        x++;
}

void Frog::reset(int startX, int startY)
{
    x = startX;
    y = startY;
}

int Frog::getX() const
{
    return x;
}

int Frog::getY() const
{
    return y;
}
