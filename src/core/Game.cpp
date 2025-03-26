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

Shader *grayscaleShader;

Game::Game(int width, int height) : windowWidth(width), windowHeight(height) {}

Game::~Game()
{
	TextureLoader::clearCache();
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

	// Инициализация Framebuffer
	framebuffer.Init(windowWidth, windowHeight);
	screenQuadRenderer = new ScreenQuadRenderer();

	// Загружаем текстуры
	Texture2D *texture1 = TextureLoader::loadTexture("assets/textures/texture.png");
	Texture2D *texture2 = TextureLoader::loadTexture("assets/textures/qweqwe1.png");
	// Загружаем шейдеров
	Shader *baseShader = ShaderLoader::loadShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.frag");
	// Shader *blurShader = ShaderLoader::loadShader("assets/shaders/blur_vertex.glsl", "assets/shaders/blur_fragment.glsl");

	grayscaleShader = ShaderLoader::loadShader("assets/shaders/grayscale_vertex.glsl", "assets/shaders/grayscale_fragment.frag");

	if (!baseShader || !grayscaleShader)
	{
		std::cout << "Failed to load Shaders!" << std::endl;
		return;
	}

	if (!texture1 || !texture2)
	{
		std::cerr << "Failed to load textures!" << std::endl;
		return;
	}

	auto obj2 = std::make_shared<GameObject>(texture1, baseShader);

	auto obj1 = std::make_shared<GameObject>(texture1, baseShader);

	gameObj.push_back(obj2);
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
	// Рендер в FBO
	framebuffer.Bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // <--- Добавить очистку

	for (const auto &obj : gameObj)
	{
		obj->Draw();
	}
	framebuffer.Unbind();

	// Применение эффекта
	ApplyGrayscaleEffect();

	// Рендер ImGui ПОСЛЕ всех эффектов
	imguiManager->DrawDebugPanel(deltaTime, gameObj.size(), gameObj[0]->dstrect);

	// Меняем буферы
	glContext.swapBuffers(window);
}

void Game::Update(float deltaTime)
{
}

void Game::ApplyGrayscaleEffect()
{
	// Используем шейдер для черно-белого эффекта
	grayscaleShader->use();

	GLuint textureID = framebuffer.GetTexture();
	if (textureID == 0)
	{
		std::cerr << "Framebuffer texture is not initialized!" << std::endl;
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Устанавливаем матрицу трансформации для отрисовки на весь экран
	glm::mat4 model = glm::ortho(0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.0f, -1.0f, 1.0f);
	grayscaleShader->setMat4("transform", model);

	// Отрисовываем текстуру на весь экран
	screenQuadRenderer->Render();
}
