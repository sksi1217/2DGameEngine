#include "GameObject.h"
#include <GL/glew.h>
#include <iostream>

GameObject::GameObject(const float *vertices, size_t vertexCount, size_t vertexSize, std::shared_ptr<Texture2D> texture, std::shared_ptr<ShaderProgram> shader)
	: vertexCount(vertexCount), texture(texture), shader(shader)
{
	if (!vertexCount)
	{
		std::cerr << "vertexCount is not loaded!" << std::endl;
		return;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

	// Атрибуты вершин (позиция и текстурные координаты)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Отвязываем VAO
}

GameObject::~GameObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void GameObject::Draw()
{
	if (!shader || !texture)
	{
		std::cerr << "Shader or texture is not loaded!" << std::endl;
		return;
	}

	shader->use();
	texture->bind();

	// Создаем матрицу преобразования
	glm::mat4 model = glm::mat4(1.0f);

	// Передаем матрицу в шейдер
	shader->setMat4("transform", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
}
