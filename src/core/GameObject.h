#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <memory>
#include <src/graphics/Render.h>

class GameObject
{
public:
	GameObject(Texture2D *texture, Shader *shader);
	~GameObject();

	void Draw();

	void SetNormalizedPosition(float normX, float normY, int windowWidth, int windowHeight);

	Rect dstrect = {0.0f, 0.0f, 100.0f, 100.0f}; // Целевой прямоугольник на экране

	glm::vec2 getPosition() const
	{
		return glm::vec2(dstrect.x, dstrect.y);
	}
	Render renderer;
	Shader *baseShader;

private:
	float normX; // Нормализованная координата X
	float normY; // Нормализованная координата Y

	Rect srcrect = {0.0f, 0.0f, 1.0f, 1.0f};
	Rect origin = {0.0f, 0.0f, 0.0f, 0.0f}; // Точка вращения

	float angle = 0;

	Texture2D *texture;
	std::vector<Shader *> effectShaders; // Список эффектов
};

#endif // RENDERABLE_H
