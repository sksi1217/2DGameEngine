#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <memory>
#include <src/graphics/ShaderProgram.h>
#include <src/graphics/Texture2D.h>

class GameObject
{
public:
	GameObject(const float *vertices, size_t vertexCount, size_t vertexSize, std::shared_ptr<Texture2D> texture, std::shared_ptr<ShaderProgram> shader);
	~GameObject();

	void Draw();

	// Методы для управления трансформациями
	void SetPosition(const glm::vec2 &pos) { Position = pos; }
	void SetOrigin(const glm::vec2 &origin) { Origin = origin; }
	void SetRotation(float angle) { Rotation = angle; }
	void SetScale(const glm::vec2 &scale) { Scale = scale; }
	void SetFlipHorizontal(bool flip) { FlipHorizontal = flip; }
	void SetFlipVertical(bool flip) { FlipVertical = flip; }

	float Rotation = 0.0f; // Угол вращения (градусы)

private:
	GLuint VAO;
	GLuint VBO;
	size_t vertexCount;
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<ShaderProgram> shader;

	glm::vec2 Position = {0.0f, 0.0f}; // Позиция объекта
	glm::vec2 Origin = {0.0f, 0.0f};   // Точка поворота (0-1)

	glm::vec2 Scale = {1.0f, 1.0f}; // Масштаб по осям
	bool FlipHorizontal = false;	// Отражение по горизонтали
	bool FlipVertical = false;		// Отражение по вертикали
};

#endif // RENDERABLE_H
