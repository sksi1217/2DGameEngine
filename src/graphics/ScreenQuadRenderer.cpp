#include "ScreenQuadRenderer.h"
#include <iostream>
#include <src/core/Rect.h>

Rect dstrect = {0.0f, 0.0f, 1.0f, 1.0f}; // Позиция и размер

ScreenQuadRenderer::ScreenQuadRenderer()
{
	// Генерация VAO и VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Проверка успешности создания
	if (VAO == 0 || VBO == 0)
	{
		std::cerr << "Failed to create VAO or VBO!" << std::endl;
		return;
	}

	// Привязка VAO
	glBindVertexArray(VAO);

	// Привязка VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Генерация вершин для целевого прямоугольника
	std::vector<float> vertices = dstrect.generateVertices();
	/*
	// Данные вершин экранного квадрата
	float vertices[] = {
		// Позиции       // Текстурные координаты
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 600.0f, 0.0f, 0.0f,
		800.0f, 600.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 1.0f,
		800.0f, 600.0f, 1.0f, 0.0f,
		800.0f, 0.0f, 1.0f, 1.0f};
*/

	// Загрузка данных в VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Настройка атрибутов вершин
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Отвязка VAO
	glBindVertexArray(0);
}
