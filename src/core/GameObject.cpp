#include "GameObject.h"
#include <GL/glew.h>
#include <iostream>

GameObject::GameObject(Texture2D *texture, Shader *shader)
	: texture(texture), shader(shader), renderer()
{
	if (!texture || !shader)
	{
		std::cerr << "Failed to initialize GameObject!" << std::endl;
	}

	srcrect = {0.0f, 16.0f, 16.0f, 16.0f};
	dstrect = {0.0f, 100.0f, 100.0f, 100.0f}; // Позиция и размер объекта
	origin = {50.0f, 0.0f, 0.0f, 0.0f};		  // Локальные координаты центра
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	if (angle >= 360)
	{
		angle = 0;
	}

	angle++;
	// Отрисовка спрайта
	renderer.RenderSprite(texture, shader, &srcrect, &dstrect, angle, &origin);
}
