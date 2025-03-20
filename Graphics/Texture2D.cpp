#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#include <GL/gl.h>
#include <iostream>

Texture2D::Texture2D() : textureID(0) {}

Texture2D::~Texture2D()
{
	if (textureID)
	{
		glDeleteTextures(1, &textureID);
	}
}

bool Texture2D::loadFromFile(const std::string &filePath)
{
	int width, height, channels;
	unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
	if (!data)
	{
		std::cerr << "Failed to load image: " << filePath << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Настройка параметров текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Загрузка данных текстуры
	GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
	return true;
}

void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

unsigned int Texture2D::getID() const
{
	return textureID;
}
