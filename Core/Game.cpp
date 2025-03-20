#include "Game.h"
#include "Resources/GameManager.h"

#include <iostream>
#include <chrono>
#include <OpenGL/OpenGLContex.h>

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
    // Рендеринг
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Пример: треугольник
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glContext.swapBuffers();
}

void Game::Update(float deltaTime)
{
}
