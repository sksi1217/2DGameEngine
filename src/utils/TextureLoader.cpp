#include "TextureLoader.h"
#include <src/graphics/Texture2D.h>
#include <memory>
#include <iostream>

// Инициализация статического кэша
std::unordered_map<std::string, std::weak_ptr<Texture2D>> TextureLoader::textureCache;

std::shared_ptr<Texture2D> TextureLoader::loadTexture(const std::string &filePath)
{
	// Проверяем, есть ли текстура в кэше
	auto it = textureCache.find(filePath);
	if (it != textureCache.end())
	{
		auto cachedTexture = it->second.lock(); // Пытаемся получить shared_ptr
		if (cachedTexture)
		{
			return cachedTexture; // Возвращаем кэшированную текстуру
		}
	}

	// Создаем новую текстуру
	auto texture = std::make_shared<Texture2D>();
	if (!texture->loadFromFile(filePath))
	{
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		return nullptr;
	}

	// Добавляем текстуру в кэш
	textureCache[filePath] = texture;
	return texture;
}
