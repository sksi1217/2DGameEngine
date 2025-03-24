#include "Game.h"
#include "GameManager.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <iostream>

#include <src/utils/ShaderLoader.h>
#include <src/utils/TextureLoader.h>
#include <chrono>
#include <iostream>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Rect.h"

Game::Game(int width, int height) : windowWidth(width), windowHeight(height) {}

Game::~Game()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Game::Initialize()
{
	// Инициализация GLFW
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	// Настройка OpenGL контекста
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Создание окна
	window = glfwCreateWindow(windowWidth, windowHeight, "ImGui + OpenGL Example", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // V-Sync

	// Инициализация GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW");
	}

	// Инициализация OpenGL контекста
	try
	{
		glContext.Initialize(window);
	}
	catch (const std::exception &e)
	{
		std::cerr << "OpenGL init error: " << e.what() << std::endl;
		return;
	}

	// Инициализация ImGuiManager (только после создания окна GLFW)
	imguiManager = std::make_unique<ImGuiManager>(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return;
	}

	// Загружаем текстуры
	Texture2D *texture1 = TextureLoader::loadTexture("assets/textures/texture.png");
	// Загружаем шейдеров
	Shader *baseShader = ShaderLoader::loadShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	Shader *blurShader = ShaderLoader::loadShader("assets/shaders/blur_vertex.glsl", "assets/shaders/blur_fragment.glsl");
	if (!baseShader || !blurShader)
	{
		std::cout << "Failed to load Shaders!" << std::endl;
		return;
	}

	if (!texture1)
	{
		std::cerr << "Failed to load textures!" << std::endl;
		return;
	}

	// auto obj1 = std::make_shared<GameObject>(texture1, shader1);

	auto obj1 = std::make_shared<GameObject>(texture1, baseShader);
	obj1->AddEffect(blurShader);

	// gameObj.push_back(obj1);
	gameObj.push_back(obj1);
}

void Game::HandleEvents()
{
	glfwPollEvents();

	ImGuiIO &io = ImGui::GetIO();
	io.DisplaySize = ImVec2(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

	// Проверка закрытия окна
	if (glfwWindowShouldClose(window))
	{
		isRunning = false;
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
	glClear(GL_COLOR_BUFFER_BIT);

	for (const auto &obj : gameObj)
	{
		obj->Draw();
		imguiManager->DrawDebugPanel(deltaTime, gameObj.size(), obj->dstrect);
	}

	// Меняем буферы
	glContext.swapBuffers(window);
}

void Game::Update(float deltaTime)
{
}
