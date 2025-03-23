#include "Render.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

Render::Render()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	// Привязываем VBO для хранения данных о вершинах
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Атрибуты вершин (позиция и текстурные координаты)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Отвязываем VAO
}

Render::~Render()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Render::RenderSprite(Texture2D *texture, Shader *shader, const Rect *srcrect, const Rect *dstrect, double angle, const Rect *origin)
{
	if (!shader || !texture)
	{
		std::cerr << "Shader or texture is not loaded!" << std::endl;
		return;
	}

	shader->use();
	texture->bind();

	// Генерация вершин для целевого прямоугольника
	std::vector<float> vertices = dstrect->generateVertices();

	// Размеры текстуры
	float textureWidth = static_cast<float>(texture->getWidth());
	float textureHeight = static_cast<float>(texture->getHeight());

	// Нормализованные координаты srcrect
	float uStart = srcrect->x / textureWidth;
	float vStart = srcrect->y / textureHeight;
	float uEnd = (srcrect->x + srcrect->w) / textureWidth;
	float vEnd = (srcrect->y + srcrect->h) / textureHeight;

	// Модификация текстурных координат в зависимости от srcrect
	for (size_t i = 3; i < vertices.size(); i += 5)
	{
		float u = vertices[i];	   // Исходная текстурная координата U
		float v = vertices[i + 1]; // Исходная текстурная координата V

		// Преобразуем текстурные координаты в соответствии с srcrect
		vertices[i] = uStart + u * (uEnd - uStart);		// Интерполируем U
		vertices[i + 1] = vStart + v * (vEnd - vStart); // Интерполируем V
	}

	// Привязываем VAO и обновляем данные в VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Матрица трансформации
	glm::mat4 model = glm::mat4(1.0f);

	// Временное решение камеры
	float left = 0.0f;
	float right = 800.0f;
	float bottom = 600.0f; // Обратите внимание: начало координат — левый верхний угол
	float top = 0.0f;
	model = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

	// Корректное применение трансформаций для вращения
	model = glm::translate(model, glm::vec3(dstrect->x, dstrect->y, 0.0f));							  // Перемещение объекта
	model = glm::translate(model, glm::vec3(dstrect->x + origin->x, dstrect->y + origin->y, 0.0f));	  // Перемещение к точке вращения
	model = glm::rotate(model, glm::radians((float)angle), glm::vec3(0.0f, 0.0f, 1.0f));			  // Поворот
	model = glm::translate(model, glm::vec3(-dstrect->x - origin->x, -dstrect->y - origin->y, 0.0f)); // Возврат к исходной позиции

	shader->setMat4("transform", model);

	// Рисуем треугольники
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindVertexArray(0); // Отвязываем VAO
}
