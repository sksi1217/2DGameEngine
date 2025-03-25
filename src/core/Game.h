#ifndef GAME_H
#define GAME_H

#include <src/graphics/Texture2D.h> // Подключаем Texture2D
#include <src/graphics/Shader.h>    // Подключаем ShaderProgram
#include <src/core/GameObject.h>
#include <src/core/ImGuiManager.h>
#include <src/openGL/OpenGLContext.h>

#include <GLFW/glfw3.h>
#include <vector>
#include <memory> // Для std::shared_ptr
#include <src/openGL/Framebuffer.h>
#include <src/graphics/ScreenQuadRenderer.h>

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

    ScreenQuadRenderer *screenQuadRenderer;

    Framebuffer framebuffer;
    GLuint VAO, VBO;

    OpenGLContext glContext;
    std::unique_ptr<ImGuiManager> imguiManager;

    GLFWwindow *window;

    void DrawTexture(
        std::shared_ptr<Texture2D> texture,
        float x, float y, float width, float height,
        float angle = 0.0f, bool flipHorizontal = false, bool flipVertical = false);

    void Initialize();
    void Run();
    void HandleEvents();
    void Draw(float deltaTime);
    void Update(float deltaTime);
    void ApplyGrayscaleEffect();
};

#endif // GAME_H
