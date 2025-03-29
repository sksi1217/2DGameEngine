#pragma once

#include <GLFW/glfw3.h>
#include <string>

class GameWindow
{
public:
	GameWindow() = default;
	~GameWindow();

	GLFWwindow *InitWindow(std::string title, int windowWidth, int windowHeight);

private:
	GLFWwindow *window;
};
