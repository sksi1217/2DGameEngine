#pragma once

#include <memory>

#include <src/graphics/Render.h>
#include <src/core/Engine.h>

class GameObject
{
public:
	GameObject(std::shared_ptr<Texture2D> texture, std::shared_ptr<Shader> shader);
	~GameObject();

	void Draw();

	Render renderer;
	std::shared_ptr<Shader> baseShader;

	Rect dstrect = {0.0f, 0.0f, 100.0f, 100.0f}; // Целевой прямоугольник на экране
private:
	Rect srcrect = {0.0f, 0.0f, 1.0f, 1.0f};
	Rect origin = {0.0f, 0.0f, 0.0f, 0.0f}; // Точка вращения

	float angle = 0;

	std::shared_ptr<Texture2D> texture;
};
