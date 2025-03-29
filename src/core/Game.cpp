#include "Game.h"

#include <iostream>
#include <chrono>

Game::Game(int width, int height) : windowWidth(width), windowHeight(height) {}

Game::~Game()
{
	TextureLoader::clearCache();
	glfwTerminate();
}

void Game::Initialize()
{
	// Инициализация окна
	window = windowGame.InitWindow("Test", windowWidth, windowHeight);

	// Инициализация GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Failed to initialize GLEW");

	// Инициализация OpenGL контекста
	glContext.Initialize(window);

	// Инициализация ImGuiManager (только после создания окна GLFW)
	imguiManager = new ImGuiManager(window);

	camera = new Camera(static_cast<float>(windowWidth),
						static_cast<float>(windowHeight));
}

void Game::LoadContent()
{
	// Загружаем текстуры
	auto texture1 = TextureLoader::loadTexture("assets/textures/texture.png");
	auto texture2 = TextureLoader::loadTexture("assets/textures/qweqwe1.png");
	// Загружаем шейдеров
	auto baseShader = ShaderLoader::loadShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.frag");

	if (!baseShader || !texture1 || !texture2)
	{
		std::cout << "Failed to load Shaders or textures!" << std::endl;
		return;
	}

	auto obj1 = std::make_shared<GameObject>(texture1, baseShader);
	auto obj2 = std::make_shared<GameObject>(texture1, baseShader);

	obj1->renderer.setCamera(camera);
	obj2->renderer.setCamera(camera);

	gameObj.push_back(obj1);
	gameObj.push_back(obj2);
}

void Game::HandleEvents()
{
	glfwPollEvents();

	// Получаем текущие размеры окна
	int newWidth, newHeight;
	glfwGetFramebufferSize(window, &newWidth, &newHeight);

	if (newWidth != windowWidth || newHeight != windowHeight)
	{
		windowWidth = newWidth;
		windowHeight = newHeight;

		// Обновляем область просмотра
		glViewport(0, 0, windowWidth, windowHeight);

		// Обновляем матрицу проекции камеры
		camera->resize(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
	}

	// ImGui
	ImGuiIO &io = ImGui::GetIO();
	io.DisplaySize = ImVec2(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

	// Проверка закрытия окна
	if (glfwWindowShouldClose(window))
		isRunning = false;
}

void Game::Start()
{
	Initialize();
	LoadContent();
	Run();
}

void Game::Run()
{
	auto lastTime = std::chrono::high_resolution_clock::now();
	while (isRunning)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		HandleEvents();

		Update(deltaTime);
		Draw(deltaTime);
	}
}

void Game::Draw(float deltaTime)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto &obj : gameObj)
	{
		obj->Draw();
	}

	imguiManager->DrawDebugPanel(deltaTime, gameObj.size(), gameObj[0]->dstrect);

	glContext.swapBuffers(window);
}

void Game::Update(float deltaTime)
{
}
