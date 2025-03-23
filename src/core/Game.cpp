#include "Game.h"
#include "GameManager.h"

#include <src/openGL/OpenGLContex.h>
#include <src/utils/ShaderLoader.h>
#include <src/utils/TextureLoader.h>
#include <chrono>
#include <iostream>

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
	std::shared_ptr<Texture2D> texture1 = TextureLoader::loadTexture("assets/textures/qweqwe.jpg");
	std::shared_ptr<Texture2D> texture2 = TextureLoader::loadTexture("assets/textures/qweqwe.png");

	if (!texture1 || !texture2)
	{
		std::cerr << "Failed to load textures!" << std::endl;
		return;
	}

	shader1 = ShaderLoader::loadShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	if (!shader1)
	{
		std::cout << "Failed to load Shaders!" << std::endl;
	}

	// Создаем объекты
	float vertices1[] = {
		// Другой объект
		-100, -70, 0.0f, 0.0f, 0.0f,
		100, -70, 0.0f, 1.0f, 0.0f,
		100, 70, 0.0f, 1.0f, 1.0f,
		-100, 70, 0.0f, 0.0f, 1.0f};

	float vertices2[] = {
		// Другой объект
		-100, -70, 0.0f, 0.0f, 0.0f,
		100, -70, 0.0f, 1.0f, 0.0f,
		100, 70, 0.0f, 1.0f, 1.0f,
		-100, 70, 0.0f, 0.0f, 1.0f};

	auto obj1 = std::make_shared<GameObject>(vertices1, 4, sizeof(vertices1), texture1, shader1);
	obj1->SetPosition({200, 300}); // Позиция объекта на экране

	auto obj = std::make_shared<GameObject>(vertices2, 4, sizeof(vertices2), texture2, shader1);
	obj->SetPosition({100, 100}); // Позиция объекта на экране
	obj->SetOrigin({0.0f, 0.0f}); // Центр вращения (центр объекта)
	obj->SetRotation(0.0f);		  // Поворот на 45 градусов
	// obj->SetScale({1.0f, 1.0f});	// Масштаб
	obj->SetFlipVertical(false); // Горизонтальное отражение

	gameObj.push_back(obj1);
	gameObj.push_back(obj);
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

		obj->Rotation++;
		if (obj->Rotation >= 360)
		{
			obj->Rotation = 0;
		}
	}

	glContext.swapBuffers();
}

void Game::Update(float deltaTime)
{
}
