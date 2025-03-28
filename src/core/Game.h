#ifndef GAME_H
#define GAME_H

#include <src/utils/ShaderLoader.h>
#include <src/utils/TextureLoader.h>
#include <src/graphics/Texture2D.h>
#include <src/graphics/Shader.h>

#include <src/include/stb_image.h>
#include <src/core/GameObject.h>
#include <src/core/ImGuiManager.h>
#include <src/openGL/OpenGLContext.h>

#include <vector>
#include <memory>
#include <src/graphics/ScreenQuadRenderer.h>
#include "Camera.h"

class Game
{
public:
    Game(int width = 800, int height = 600);
    ~Game();

    void Start();

    std::vector<GameObject *> gameObj;

private:
    // GameWindow gameWindow; // Используем новый класс
    int windowWidth = 800;
    int windowHeight = 600;
    bool isRunning = true;
    float deltaTime = 0;

    OpenGLContext glContext;
    std::unique_ptr<ImGuiManager> imguiManager;

    Camera *camera;
    GLFWwindow *window;

    void Initialize();
    void LoadContent();
    void Run();
    void HandleEvents();
    void Draw(float deltaTime);
    void Update(float deltaTime);
};

#endif // GAME_H
