#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram() : programID(0) {}

ShaderProgram::~ShaderProgram()
{
	if (programID != 0)
	{
		glDeleteProgram(programID);
	}
}

bool ShaderProgram::loadFromFile(const std::string &vertexPath, const std::string &fragmentPath)
{
	// Загрузка исходного кода шейдеров
	std::string vertexSource = loadShaderSource(vertexPath);
	std::string fragmentSource = loadShaderSource(fragmentPath);

	if (vertexSource.empty() || fragmentSource.empty())
	{
		std::cerr << "Failed to load shader source files." << std::endl;
		return false;
	}

	// Компиляция шейдеров
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	if (vertexShader == 0 || fragmentShader == 0)
	{
		return false;
	}

	// Создание программы
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	// Проверка успешности связывания
	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		std::cerr << "Shader program linking failed: " << infoLog << std::endl;
		return false;
	}

	// Очистка скомпилированных шейдеров
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

GLuint ShaderProgram::compileShader(GLenum type, const std::string &source)
{
	GLuint shader = glCreateShader(type);
	if (shader == 0)
	{
		std::cerr << "Failed to create shader of type: " << type << std::endl;
		return 0;
	}

	const char *sourceCStr = source.c_str();
	glShaderSource(shader, 1, &sourceCStr, nullptr);
	glCompileShader(shader);

	// Проверка успешности компиляции
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed: " << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

std::string ShaderProgram::loadShaderSource(const std::string &filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}

void ShaderProgram::use() const
{
	glUseProgram(programID);
}

GLuint ShaderProgram::getProgramID() const
{
	return programID;
}

// Новый метод для установки uniform-переменной типа mat4
void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &matrix) const
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location == -1)
	{
		std::cerr << "Uniform variable not found: " << name << std::endl;
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
