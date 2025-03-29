#pragma once

#include <GLFW/glfw3.h>
#include <GL/glx.h>
#include <stdexcept>
#include <iostream>

class OpenGLContext
{
public:
    OpenGLContext();

    ~OpenGLContext();

    void Initialize(GLFWwindow *window);

    void swapBuffers(GLFWwindow *window) const;

    bool isValid() const;

private:
    GLXContext context = nullptr;
};
