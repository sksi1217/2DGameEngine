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

	srcrect = {0.0f, 0.0f, 32.0f, 32.0f};
	dstrect = {100.0f, 100.0f, 100.0f, 100.0f}; // Позиция и размер объекта
	origin = {50.0f, 50.0f, 0.0f, 0.0f};		// Локальные координаты центра
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	// Отрисовка спрайта
	// renderer.RenderSprite(texture, shader, &srcrect, &dstrect, angle, &origin);

	// Применяем базовый шейдер
	renderer.RenderSprite(texture, baseShader, &srcrect, &dstrect, angle, &origin);

	// Применяем эффекты
	for (auto *effectShader : effectShaders)
	{
		effectShader->use();
		effectShader->setFloat("blurRadius", 5.0f);						// Радиус размытия
		effectShader->setVec2("texOffset", glm::vec2(1.0f / 32, 0.0f)); // Смещение по горизонтали
		renderer.RenderSprite(texture, effectShader, &srcrect, &dstrect, angle, &origin);
	}
}

void GameObject::AddEffect(Shader *effectShader)
{
	effectShaders.push_back(effectShader);
}
