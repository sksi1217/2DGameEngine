#include "Resources/GameManager.h"

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <stdexcept>
#include <iostream>

class OpenGLContext
{
public:
    OpenGLContext();

    ~OpenGLContext();

    void Initialize();

    void swapBuffers() const;

    bool isValid() const;

private:
    GLXContext context = nullptr;
};
