#include "Game.h"
#include "Resources/GameManager.h"

#include <iostream>
#include <chrono>
#include <OpenGL/OpenGLContex.h>
#include <Utils/TextureLoader.h>
#include <Utils/ShaderLoader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

OpenGLContext glContext;

// Загружаем и привязываем текстуру
std::shared_ptr<Texture2D> texture1;

// Загрузка шейдеров
std::shared_ptr<ShaderProgram> shader1;

Game::Game(int width, int height) : gameWindow(width, height) {}

Game::~Game()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

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

    // Загружаем текстуры
    std::shared_ptr<Texture2D> texture1 = TextureLoader::loadTexture("Resources/Textures/qweqwe.jpg");
    std::shared_ptr<Texture2D> texture2 = TextureLoader::loadTexture("Resources/Textures/qweqwe.png");

    if (!texture1 || !texture2)
    {
        std::cerr << "Failed to load textures!" << std::endl;
        return;
    }

    shader1 = ShaderLoader::loadShader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    if (!shader1)
    {
        std::cout << "Failed to load Shaders!" << std::endl;
    }

    // Создаем объекты
    float vertices1[] = {
        // Позиции          // Текстурные координаты
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

    float vertices2[] = {
        // Другой объект
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    gameObj.push_back(std::make_shared<GameObject>(vertices1, 4, sizeof(vertices1), texture1, shader1));
    gameObj.push_back(std::make_shared<GameObject>(vertices2, 4, sizeof(vertices2), texture2, shader1));
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
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto &obj : gameObj)
    {
        obj->Draw();
    }

    glContext.swapBuffers();
}

void Game::Update(float deltaTime)
{
}

void Game::DrawTexture(
    std::shared_ptr<Texture2D> texture,
    float x, float y, float width, float height,
    float angle, bool flipHorizontal, bool flipVertical)
{
    if (!shader1 || !texture)
    {
        std::cerr << "Shader or texture is not loaded!" << std::endl;
        return;
    }

    // Активируем шейдерную программу
    shader1->use();

    // Создаем матрицу преобразования
    glm::mat4 model = glm::mat4(1.0f);

    // Перемещение
    model = glm::translate(model, glm::vec3(x, y, 0.0f));

    // Масштабирование
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    // Поворот вокруг центра объекта
    model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));

    // Отражение
    if (flipHorizontal)
    {
        model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
    }
    if (flipVertical)
    {
        model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    }

    // Передаем матрицу в шейдер
    shader1->setMat4("transform", model);

    // Привязываем VAO
    glBindVertexArray(VAO);

    // Рисуем квадрат
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
