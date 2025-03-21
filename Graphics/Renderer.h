#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture2D.h"

class Renderer
{
public:
	// Рисует текстуру с учетом позиции, размера, поворота и отражения
	static void DrawTexture(
		std::shared_ptr<ShaderProgram> shader,
		std::shared_ptr<Texture2D> texture,
		float x, float y, float width, float height,
		float angle = 0.0f, bool flipHorizontal = false, bool flipVertical = false);

private:
	// Приватные методы или переменные (если нужны)
};

#endif // RENDERER_H
