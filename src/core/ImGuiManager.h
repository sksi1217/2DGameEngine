#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include "Rect.h"

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

#endif // IMGUI_MANAGER_H
