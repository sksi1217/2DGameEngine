// TextureLoader.h
#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <unordered_map>

class Texture2D;

class TextureLoader
{
public:
	// Загрузка текстуры (с кэшированием)
	static Texture2D *loadTexture(const std::string &filePath);

	// Очистка кэша
	static void clearCache();

private:
	// Кэш загруженных текстур
	static std::unordered_map<std::string, Texture2D *> textureCache;

	// Приватный конструктор (класс статический)
	TextureLoader() = delete;
};

#endif // TEXTURELOADER_H
