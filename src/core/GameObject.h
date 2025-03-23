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

	Rect dstrect = {0.0f, 0.0f, 100.0f, 100.0f}; // Целевой прямоугольник на экране

private:
	Render renderer;

	Rect srcrect = {0.0f, 0.0f, 1.0f, 1.0f};
	Rect origin = {0.0f, 0.0f, 0.0f, 0.0f}; // Точка вращения

	float angle = 0;

	Texture2D *texture;
	Shader *shader;
};

#endif // RENDERABLE_H
