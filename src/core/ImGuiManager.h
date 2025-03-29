#pragma once
#define GLEW_STATIC		  // Для статической линковки GLEW
#define GLFW_INCLUDE_NONE // Отключает автоматическое включение gl.h в GLFW
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <src/core/Engine.h>

class ImGuiManager
{
public:
	ImGuiManager(GLFWwindow *window);
	~ImGuiManager();

	void DrawDebugPanel(float deltaTime, size_t gameObjectsCount, Rect &x);

private:
	float lastFrameTime;
	GLFWwindow *window;
};
