#include "Framebuffer.h"
#include <iostream>

Framebuffer::Framebuffer()
	: m_Framebuffer(0), m_Texture(0), m_Renderbuffer(0) {}

Framebuffer::~Framebuffer()
{
	Delete();
}

void Framebuffer::Init(unsigned int width, unsigned int height)
{
	// ? Удаляем предыдущие ресурсы
	Delete();

	// ? Создаем FBO
	glGenFramebuffers(1, &m_Framebuffer);

	// ? FBO Привязываем
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

	// ? Создаем текстуру для цвета
	// ? Создаем текстуру
	glGenTextures(1, &m_Texture);

	// ? делает текстуру активной
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// ? Настройка параметров текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// ? Загрузка данных текстуры
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	// ? Прикрепляем текстуру к FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

	// ? Создаем рендербуфер для глубины и трафарета
	glGenRenderbuffers(1, &m_Renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_Renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Renderbuffer);

	// ? Проверка на ошибки
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer is not complete!\n"
				  << std::endl;
	}

	// ? Возвращаем привязку к дефолтному фреймбуферу
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Framebuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
}

void Framebuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Delete()
{
	if (m_Framebuffer)
	{
		glDeleteFramebuffers(1, &m_Framebuffer);
		m_Framebuffer = 0;
	}
	if (m_Texture)
	{
		glDeleteTextures(1, &m_Texture);
		m_Texture = 0;
	}
	if (m_Renderbuffer)
	{
		glDeleteRenderbuffers(1, &m_Renderbuffer);
		m_Renderbuffer = 0;
	}
}
