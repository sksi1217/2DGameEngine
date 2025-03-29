#include "GameObject.h"

#include <GL/glew.h>
#include <iostream>

GameObject::GameObject(std::shared_ptr<Texture2D> texture, std::shared_ptr<Shader> shader)
	: renderer(), baseShader(shader), dstrect({0.0f, 0.0f, 100.0f, 100.0f}), srcrect({0.0f, 0.0f, 32.0f, 32.0f}), origin({50.0f, 50.0f, 0.0f, 0.0f}), angle(0), texture(texture)
{
	srcrect = {0.0f, 0.0f, 32.0f, 32.0f};	// позиция и размер текстуры
	dstrect = {0.0f, 0.0f, 100.0f, 100.0f}; // Позиция и размер объекта
	origin = {50.0f, 50.0f, 0.0f, 0.0f};	// Локальные координаты центра

	if (!texture || !baseShader)
	{
		throw std::invalid_argument("Texture or shader is null!");
	}
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	renderer.RenderSprite(texture.get(), baseShader.get(), srcrect, dstrect, angle, origin);
}
