#ifndef RECT_H
#define RECT_H

#include <vector>

struct Rect
{
	float x, y; // Позиция левого нижнего угла
	float w, h; // Ширина и высота

	// Метод для генерации массива вершин
	std::vector<float> generateVertices() const
	{
		std::vector<float> vertices = {
			// Левый нижний угол
			x, y, 0.0f, 0.0f, 0.0f,

			// Правый нижний угол
			x + w, y, 0.0f, 1.0f, 0.0f,

			// Правый верхний угол
			x + w, y + h, 0.0f, 1.0f, 1.0f,

			// Левый верхний угол
			x, y + h, 0.0f, 0.0f, 1.0f};
		return vertices;
	}
};

#endif // RECT_H
