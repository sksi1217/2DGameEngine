#include "GameWindow.h"

GameWindow::GameWindow(int width, int height)
{
#ifdef _WIN32
    window = std::make_unique<Win32Window>(width, height);
#elif __linux__
    window = std::make_unique<X11Window>(width, height);
#endif
}

GameWindow::~GameWindow()
{
}

bool GameWindow::ProcessEvents()
{
    return window->ProcessEvents();
}
