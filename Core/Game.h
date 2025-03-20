#ifndef GAME_H
#define GAME_H

#include "GameWindow.h"

class Game
{
public:
    Game(int width = 640, int height = 480);

    void Start();

private:
    GameWindow gameWindow; // Используем новый класс

    bool isRunning = true;
    float deltaTime = 0;

    void Initialize();

    void HandleEvents();
    void Draw();
    void Update(float deltaTime);
};

#endif // GAME_H
