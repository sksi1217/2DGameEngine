#include "Game.h"
#include "Resources/GameManager.h"
#include "Graphics/Texture2D.h"

#include <iostream>
#include <chrono>
#include <OpenGL/OpenGLContex.h>
#include <Utils/TextureLoader.h>

OpenGLContext glContext;

Game::Game(int width, int height) : gameWindow(width, height) {}

void Game::Initialize()
{
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

    // 3. Создание контекста OpenGL
    try
    {
        glContext.Initialize();
    }
    catch (const std::exception &e)
    {
        std::cerr << "OpenGL init error: " << e.what() << std::endl;
        return;
    }

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

    // 5. Очистка
    XDestroyWindow(GameManager::display, GameManager::window);
    XCloseDisplay(GameManager::display);
}

void Game::Draw()
{
    // Очистка экрана
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Включение текстур
    glEnable(GL_TEXTURE_2D);

    // Загружаем и привязываем текстуру
    auto texture1 = TextureLoader::loadTexture("Resources/Textures/qweqwe.png");
    if (!texture1)
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return;
    }
    texture1->bind();

    // Рисование квадрата с текстурой
    glBegin(GL_QUADS);

    glVertex2f(-0.5f, -0.5f); // Левый нижний угол
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f); // Правый нижний угол
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0.5f, 0.5f); // Правый верхний угол
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-0.5f, 0.5f); // Левый верхний угол

    glTexCoord2f(0.0f, 0.0f);

    glEnd();

    // Отключение текстур
    glDisable(GL_TEXTURE_2D);

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
