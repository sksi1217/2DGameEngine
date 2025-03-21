#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <GL/glew.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	// Загрузка шейдеров из файлов
	bool loadFromFile(const std::string &vertexPath, const std::string &fragmentPath);

	// Использование программы
	void use() const;

	// Получение ID программы
	GLuint getProgramID() const;

private:
	GLuint programID; // ID шейдерной программы в OpenGL

	// Вспомогательные методы
	GLuint compileShader(GLenum type, const std::string &source);
	std::string loadShaderSource(const std::string &filePath);
};

#endif // SHADERPROGRAM_H
