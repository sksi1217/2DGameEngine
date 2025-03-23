#include "Game.h"
#include "GameManager.h"

#include <src/openGL/OpenGLContex.h>
#include <src/utils/ShaderLoader.h>
#include <src/utils/TextureLoader.h>
#include <chrono>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Rect.h"

OpenGLContext glContext;

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

	Shader *shader1 = ShaderLoader::loadShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	if (!shader1)
	{
		std::cout << "Failed to load Shaders!" << std::endl;
	}

	// Загружаем текстуры
	Texture2D *texture1 = TextureLoader::loadTexture("assets/textures/texture.png");

	if (!texture1)
	{
		std::cerr << "Failed to load textures!" << std::endl;
		return;
	}

	// auto obj1 = std::make_shared<GameObject>(texture1, shader1);

	auto obj1 = std::make_shared<GameObject>(texture1, shader1);

	// gameObj.push_back(obj1);
	gameObj.push_back(obj1);
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
		Draw(deltaTime);
		HandleEvents();
	}
	XDestroyWindow(GameManager::display, GameManager::window);
	XCloseDisplay(GameManager::display);
}

void Game::Draw(float deltaTime)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const auto &obj : gameObj)
	{
		obj->Draw();

		// Обновление позиции
		obj->dstrect.x += obj->speed * deltaTime;

		// Проверка границ (например, экран 800x600)
		float rightBorder = 400.0f - obj->dstrect.w; // Правая граница с учетом ширины объекта
		if (obj->dstrect.x >= rightBorder)
		{
			obj->dstrect.x = rightBorder; // Корректировка позиции
			obj->speed *= -1;			  // Инверсия направления
		}
		if (obj->dstrect.x <= 0.0f)
		{
			obj->dstrect.x = 0.0f;
			obj->speed *= -1;
		}
	}

	glContext.swapBuffers();
}

void Game::Update(float deltaTime)
{
}
