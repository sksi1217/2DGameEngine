#ifndef GAME_H
#define GAME_H

#include <src/graphics/Texture2D.h> // Подключаем Texture2D
#include <src/graphics/Shader.h>    // Подключаем ShaderProgram
#include "GameObject.h"
#include "GameWindow.h"

#include <vector>
#include <memory> // Для std::shared_ptr

class Game
{
public:
    Game(int width = 800, int height = 600);
    ~Game();

    void Start();

    std::vector<std::shared_ptr<GameObject>> gameObj;

private:
    GameWindow gameWindow; // Используем новый класс
    bool isRunning = true;
    float deltaTime = 0;
    GLuint VAO, VBO;

    void DrawTexture(
        std::shared_ptr<Texture2D> texture,
        float x, float y, float width, float height,
        float angle = 0.0f, bool flipHorizontal = false, bool flipVertical = false);

    void Initialize();
    void Run();
    void HandleEvents();
    void Draw(float deltaTime);
    void Update(float deltaTime);
};

#endif // GAME_H
