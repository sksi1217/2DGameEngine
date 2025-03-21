#include "Game.h"
#include "Resources/GameManager.h"
#include "Graphics/Texture2D.h"
#include "Graphics/ShaderProgram.h"

#include <iostream>
#include <chrono>
#include <OpenGL/OpenGLContex.h>
#include <Utils/TextureLoader.h>
#include <Utils/ShaderLoader.h>

OpenGLContext glContext;

// Загружаем и привязываем текстуру
std::shared_ptr<Texture2D> texture1;

// Загрузка шейдеров
std::shared_ptr<ShaderProgram> shader1;
std::shared_ptr<ShaderProgram> shader2;

Game::Game(int width, int height) : gameWindow(width, height) {}

void Game::Initialize()
{
    try
    {
        glContext.Initialize();
    }
    catch (const std::exception &e)
    {
        std::cerr << "OpenGL init error: " << e.what() << std::endl;
        return;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        return;
    }

    texture1 = TextureLoader::loadTexture("Resources/Textures/qweqwe.jpg");
    if (!texture1)
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return;
    }

    shader1 = ShaderLoader::loadShader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    shader2 = ShaderLoader::loadShader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    if (!shader1 && !shader2)
    {
        std::cout << "Failed to load Shaders!" << std::endl;
    }
}

void Game::HandleEvents()
{
    // Обрабатываем события через GameWindow
    if (!gameWindow.ProcessEvents())
    {
        isRunning = false; // Завершаем, если окно закрыто
    }
}

void Game::Start()
{
    Initialize();
    Run();
}

void Game::Run()
{
    // Переменные для расчета времени
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (isRunning)
    {
        // Рассчитываем deltaTime
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        Update(deltaTime);
        Draw();
        HandleEvents();
    }
    XDestroyWindow(GameManager::display, GameManager::window);
    XCloseDisplay(GameManager::display);
}

void Game::Draw()
{
    if (!shader1)
    {
        exit(true);
        std::cerr << "Shader is not loaded!" << std::endl;
        return;
    }

    // Очистка экрана
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Привязываем шейдерную программу
    shader1->use();

    // Привязываем текстуру
    // texture1->bind();

    // Настройка VAO и VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Вершины квадрата (позиции + текстурные координаты)
    float vertices[] = {
        // Позиции          // Текстурные координаты
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Левый нижний угол
        0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // Правый нижний угол
        0.5f, 0.5f, 0.0f, -1.0f, -1.0f, // Правый верхний угол
        -0.5f, 0.5f, 0.0f, 0.0f, -1.0f  // Левый верхний угол
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Атрибуты вершин
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Рисуем квадрат
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Заменяем GL_QUADS на GL_TRIANGLE_FAN


    // Очищаем VAO и VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Проверка ошибок OpenGL
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    // Показать результат на экране
    glContext.swapBuffers();
}

void Game::Update(float deltaTime)
{
}
