#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Renderer::DrawTexture(
	std::shared_ptr<ShaderProgram> shader,
	std::shared_ptr<Texture2D> texture,
	float x, float y, float width, float height,
	float angle, bool flipHorizontal, bool flipVertical)
{
	if (!shader || !texture)
	{
		std::cerr << "Shader or texture is not loaded!" << std::endl;
		return;
	}

	// Активируем шейдерную программу
	shader->use();

	// Создаем матрицу преобразования
	glm::mat4 model = glm::mat4(1.0f);

	// Перемещение
	model = glm::translate(model, glm::vec3(x, y, 0.0f));

	// Масштабирование
	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	// Поворот вокруг центра объекта
	model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));

	// Отражение
	if (flipHorizontal)
	{
		model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	if (flipVertical)
	{
		model = glm::scale(model, glm::vec3(1.0f, -1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
	}

	// Передаем матрицу в шейдер
	shader->setMat4("transform", model);

	// Привязываем VAO
	glBindVertexArray(VAO);

	// Рисуем квадрат
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
