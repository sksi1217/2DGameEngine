#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <unordered_map>
#include <memory>

class Texture2D; // Предварительное объявление

class TextureLoader
{
public:
	// Загрузка текстуры (с кэшированием)
	static std::shared_ptr<Texture2D> loadTexture(const std::string &filePath);

private:
	// Кэш загруженных текстур
	static std::unordered_map<std::string, std::weak_ptr<Texture2D>> textureCache;

	// Приватный конструктор (класс статический)
	TextureLoader() = delete;
};

#endif // TEXTURELOADER_H
