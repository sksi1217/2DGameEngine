#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	// Загрузка текстуры из файла
	bool loadFromFile(const std::string &filePath);

	void bind() const;
	// Получение ID текстуры
	unsigned int getID() const;

private:
	unsigned int textureID; // ID текстуры в OpenGL
};

#endif // TEXTURE2D_H
