#include "GameWindow.h"
#include <stdexcept>

GLFWwindow *GameWindow::InitWindow(std::string title, int windowWidth, int windowHeight)
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
	window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), nullptr, nullptr);

	// Проверка
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // V-Sync

	return window;
}

GameWindow::~GameWindow()
{
	glfwDestroyWindow(window);
}
