#ifndef FROG_H
#define FROG_H



class Frog
{
public:
    Frog(int startX, int startY);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void reset(int startX, int startY);

    int getX() const;
    int getY() const;

    // Used to keep frog inside the screen
    void setBounds(int width, int height);

private:
    int x;
    int y;

    int screenWidth;
    int screenHeight;
};


#endif //FROG_H
