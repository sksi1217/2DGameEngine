#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <iostream>

OpenGLContext::OpenGLContext()
{
}

OpenGLContext::~OpenGLContext()
{
    // GLFW автоматически уничтожает контекст OpenGL при завершении работы,
    // поэтому здесь ничего делать не нужно.
}

void OpenGLContext::Initialize(GLFWwindow *window)
{
    try
    {
        if (!window)
        {
            throw std::runtime_error("Invalid GLFW window handle");
        }

        // Связываем контекст OpenGL с текущим окном GLFW
        glfwMakeContextCurrent(window);

        // Проверка версии OpenGL
        if (glGetString(GL_VERSION) == nullptr)
        {
            throw std::runtime_error("Failed to initialize OpenGL context");
        }

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "OpenGL init error: " << e.what() << std::endl;
        return;
    }
}

void OpenGLContext::swapBuffers(GLFWwindow *window) const
{
    if (!window)
    {
        throw std::runtime_error("Invalid GLFW window handle");
    }

    // Меняем буферы (двойная буферизация)
    glfwSwapBuffers(window);
}

bool OpenGLContext::isValid() const
{
    // В GLFW проверка контекста не требуется, так как он всегда активен,
    // если окно создано успешно.
    return true;
}
