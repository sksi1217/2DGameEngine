#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	// Загрузка текстуры из файла
	bool createTextureFromFile(const std::string &filePath);

	void bind() const;
	// Получение ID текстуры
	unsigned int getID() const;

	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	int width = 0;			// Ширина текстуры
	int height = 0;			// Высота текстуры
	unsigned int textureID; // ID текстуры в OpenGL
};

#endif // TEXTURE2D_H
