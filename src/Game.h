#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Frog.h"
#include "Lane.h"
#include "Input.h"

class Game
{
public:
    Game(int width, int height);

    void handleInput(Input input);
    void update(float deltaTime);

    // Game state queries
    bool isGameOver() const;
    bool isLevelComplete() const;

    // Accessors for rendering
    const Frog& getFrog() const;
    const std::vector<Lane>& getLanes() const;
    int getLevel() const;

private:
    void nextLevel();
    void checkCollisions();

    int screenWidth;
    int screenHeight;

    int level;
    bool gameOver;
    bool levelComplete;

    Frog frog;
    std::vector<Lane> lanes;
};


#endif //GAME_H
