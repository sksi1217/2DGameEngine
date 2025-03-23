#include "ShaderLoader.h"
#include <src/graphics/ShaderProgram.h>
#include <iostream>

// Инициализация статического кэша
std::unordered_map<ShaderLoader::ShaderKey, std::weak_ptr<ShaderProgram>, ShaderLoader::ShaderKeyHash> ShaderLoader::shaderCache;

std::shared_ptr<ShaderProgram> ShaderLoader::loadShader(const std::string &vertexPath, const std::string &fragmentPath)
{
	//  Создаем ключ для поиска в кэше
	ShaderKey key{vertexPath, fragmentPath};

	// Проверяем, есть ли шейдер в кэше
	auto it = shaderCache.find(key);
	if (it != shaderCache.end())
	{
		auto cachedShader = it->second.lock(); // Пытаемся получить shared_ptr
		if (cachedShader)
		{
			return cachedShader; // Возвращаем кэшированный шейдер
		}
	}

	// Создаем новый шейдер
	auto shader = std::make_shared<ShaderProgram>();
	if (!shader->loadFromFile(vertexPath, fragmentPath))
	{
		std::cerr << "Failed to load shader: Vertex(" << vertexPath << "), Fragment(" << fragmentPath << ")" << std::endl;
		return nullptr;
	}

	// Добавляем шейдер в кэш
	shaderCache[key] = shader;
	return shader;
}

/*
Как всё это работает вместе?
	Добавление шейдера в кэш:
		Когда вы вызываете `loadShader("vertex.glsl", "fragment.glsl")`, создается объект `ShaderKey`:
```c++
	ShaderKey key{"vertex.glsl", "fragment.glsl"};
```

Поиск в кэше:
	unordered_map использует хеш-функцию (ShaderKeyHash) для вычисления хеша ключа.
	Затем он сравнивает ключи с помощью оператора `operator==`.

Если шейдер найден:
	Возвращается существующий объект из кэша.

Если шейдер не найден:
	Создается новый объект ShaderProgram и добавляется в кэш.

*/
