#include "GameObject.h"
#include <GL/glew.h>
#include <iostream>

GameObject::GameObject(Texture2D *texture, Shader *baseShader)
	: texture(texture), baseShader(baseShader), renderer()
{
	if (!texture || !baseShader)
	{
		std::cerr << "Failed to initialize GameObject!" << std::endl;
	}

	srcrect = {0.0f, 0.0f, 32.0f, 32.0f};	// позиция и размер текстуры
	dstrect = {0.0f, 0.0f, 100.0f, 100.0f}; // Позиция и размер объекта
	origin = {100.0f, 0.0f, 0.0f, 0.0f};	// Локальные координаты центра
}

GameObject::~GameObject()
{
	delete this;
}

void GameObject::Draw()
{

	if (angle >= 360)
	{
		angle = 0;
	}

	angle++;

	renderer.RenderSprite(texture, baseShader, &srcrect, &dstrect, angle, &origin);
}
