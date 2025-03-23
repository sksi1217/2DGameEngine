#include "OpenGLContex.h"

OpenGLContext::OpenGLContext()
{
}

OpenGLContext::~OpenGLContext()
{
    if (context)
    {
        glXDestroyContext(GameManager::display, context);
    }
}

void OpenGLContext::Initialize()
{
    // 1. Выбор визуального формата
    static int visualAttribs[] = {
        GLX_RGBA,            // режим цвета RGBA (красный, зеленый, синий, альфа).
        GLX_DOUBLEBUFFER,    // двойная буферизация (для предотвращения мерцания).
        GLX_DEPTH_SIZE, 24,  // размер буфера глубины (для 3D графики).
        GLX_STENCIL_SIZE, 8, // размер буфера трафарета (для масок и эффектов).

        // размеры компонентов цвета (8 бит для каждого канала).
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,

        None};

    XVisualInfo *visualInfo = glXChooseVisual(GameManager::display, DefaultScreen(GameManager::display), visualAttribs);

    if (!visualInfo)
    {
        throw std::runtime_error("Failed to choose visual info");
    }

    // 2. Создание контекста OpenGL
    context = glXCreateContext(GameManager::display, visualInfo, nullptr, True);
    if (!context)
    {
        XFree(visualInfo);
        throw std::runtime_error("Failed to create GLX context");
    }

    XFree(visualInfo);

    // 3. Связывание контекста с окном
    if (!glXMakeCurrent(GameManager::display, GameManager::window, context))
    {
        throw std::runtime_error("Failed to bind GLX context");
    }

    // Проверка версии OpenGL
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

void OpenGLContext::swapBuffers() const
{
    glXSwapBuffers(GameManager::display, GameManager::window);
}

bool OpenGLContext::isValid() const
{
    return context != nullptr;
}
