#include "ImGuiManager.h"

ImGuiManager::ImGuiManager(GLFWwindow *window) : window(window)
{
	// Инициализация ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); // Создаем контекст ImGui
	ImGuiIO &io = ImGui::GetIO();
	io.DisplaySize = ImVec2(800, 600); // Размер окна по умолчанию

	// Установка стиля
	ImGui::StyleColorsDark();

	// Инициализация бэкендов
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

ImGuiManager::~ImGuiManager()
{
	// Очистка ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::DrawDebugPanel(float deltaTime, size_t gameObjectsCount, Rect &x)
{
	// Начало нового кадра ImGui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static float fps = 0.0f;

	// Расчет FPS
	lastFrameTime += deltaTime;
	if (lastFrameTime >= 1.0f)
	{
		fps = 1.0f / deltaTime;
		lastFrameTime = 0.0f;
	}

	// Отрисовка панели отладки
	ImGui::Begin("Debug Panel");
	ImGui::Text("FPS: %.1f", fps);
	ImGui::Text("Delta Time: %.3f ms", deltaTime * 1000.0f);
	ImGui::Text("Game Objects: %zu", gameObjectsCount);
	ImGui::SliderFloat("Floatx", &x.x, 0.0f, 500.0f);
	ImGui::SliderFloat("Floaty", &x.y, 0.0f, 300.0f);
	if (ImGui::Button("Close"))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE); // Закрытие окна через GLFW
	}
	ImGui::End();

	// Завершение кадра ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
