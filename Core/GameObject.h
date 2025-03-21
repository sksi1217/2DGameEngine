#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <memory>
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture2D.h"

class GameObject
{
public:
	GameObject(const float *vertices, size_t vertexCount, size_t vertexSize, std::shared_ptr<Texture2D> texture, std::shared_ptr<ShaderProgram> shader);
	~GameObject();

	void Draw();

private:
	GLuint VAO;
	GLuint VBO;
	size_t vertexCount;
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<ShaderProgram> shader;
};

#endif // RENDERABLE_H
