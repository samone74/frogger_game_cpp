#include "Game.h"

Game::Game(int width, int height)
    : screenWidth(width),
      screenHeight(height),
      level(1),
      gameOver(false),
      levelComplete(false),
      frog(width / 2, height - 1)
{
    frog.setBounds(screenWidth, screenHeight);
    nextLevel();
}

void Game::handleInput(Input input)
{
    if (gameOver)
        return;

    frog.moveUp();
    switch (input)
    {
        case Input::UP:    frog.moveUp();    break;
        case Input::DOWN:  frog.moveDown();  break;
        case Input::LEFT:  frog.moveLeft();  break;
        case Input::RIGHT: frog.moveRight(); break;
        default: break;
    }
}

void Game::update(float deltaTime)
{
    if (gameOver)
        return;

    levelComplete = false;

    for (auto& lane : lanes)
        lane.update(deltaTime, screenWidth);

    checkCollisions();

    // Reached top of screen → level complete
    if (frog.getY() == 0)
        levelComplete = true;

    if (levelComplete)
        nextLevel();
}

void Game::checkCollisions()
{
    for (const auto& lane : lanes)
    {
        if (lane.getY() != frog.getY())
            continue;

        if (lane.hasCarAt(frog.getX()))
        {
            gameOver = true;
            return;
        }
    }
}

void Game::nextLevel()
{
    lanes.clear();

    // Create one lane per level
    for (int i = 0; i < level; ++i)
    {
        int laneY = screenHeight - 2 - i;
        int direction = (i % 2 == 0) ? 1 : -1;
        float speed = 2.0f + level * 0.5f;

        lanes.emplace_back(laneY, direction, speed);
    }

    frog.reset(screenWidth / 2, screenHeight - 1);
    level++;
}

bool Game::isGameOver() const
{
    return gameOver;
}

bool Game::isLevelComplete() const
{
    return levelComplete;
}

const Frog& Game::getFrog() const
{
    return frog;
}

const std::vector<Lane>& Game::getLanes() const
{
    return lanes;
}

int Game::getLevel() const
{
    return level;
}
