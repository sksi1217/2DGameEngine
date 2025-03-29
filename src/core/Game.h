#pragma once
#define GLEW_STATIC       // Для статической линковки GLEW
#define GLFW_INCLUDE_NONE // Отключает автоматическое включение gl.h в GLFW
#include <src/utils/ShaderLoader.h>
#include <src/utils/TextureLoader.h>

#include <src/core/Engine.h>
#include <src/graphics/Shader.h>

#include <src/core/GameObject.h>
#include <src/openGL/OpenGLContext.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <src/core/ImGuiManager.h>

#include <src/core/GameWindow.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>

#include "Camera.h"

class Game
{
public:
    Game(int width = 800, int height = 600);
    ~Game();

    void Start();

    std::vector<std::shared_ptr<GameObject>> gameObj;

private:
    // GameWindow gameWindow; // Используем новый класс
    int windowWidth = 800;
    int windowHeight = 600;
    bool isRunning = true;
    float deltaTime = 0;

    GameWindow windowGame;
    OpenGLContext glContext;

    ImGuiManager *imguiManager;
    Camera *camera;
    GLFWwindow *window;

    void Initialize();
    void LoadContent();
    void Run();
    void HandleEvents();
    void Draw(float deltaTime);
    void Update(float deltaTime);
};
