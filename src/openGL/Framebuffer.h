#pragma once

#include <GL/glew.h>

class Framebuffer
{
public:
	Framebuffer();
	~Framebuffer();

	void Init(unsigned int width, unsigned int height);
	void Bind() const;
	void Unbind() const;
	void Delete();

	GLuint GetTexture() const { return m_Texture; }
	GLuint GetFramebuffer() const { return m_Framebuffer; }

private:
	GLuint m_Framebuffer;
	GLuint m_Texture;
	GLuint m_Renderbuffer;
};
