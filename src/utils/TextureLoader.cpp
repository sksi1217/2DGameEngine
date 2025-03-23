// TextureLoader.cpp
#include "TextureLoader.h"
#include <src/graphics/Texture2D.h>
#include <iostream>

// Инициализация статического кэша
std::unordered_map<std::string, Texture2D *> TextureLoader::textureCache;

Texture2D *TextureLoader::loadTexture(const std::string &filePath)
{
	auto it = textureCache.find(filePath);
	if (it != textureCache.end())
	{
		return it->second; // Возвращаем кэшированную текстуру
	}

	// Создаем новую текстуру
	Texture2D *texture = new Texture2D();
	if (!texture->loadFromFile(filePath))
	{
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		delete texture;
		return nullptr;
	}

	// Добавляем текстуру в кэш
	textureCache[filePath] = texture;
	return texture;
}

void TextureLoader::clearCache()
{
	for (auto &pair : textureCache)
	{
		delete pair.second; // Освобождаем память
	}
	textureCache.clear();
}
