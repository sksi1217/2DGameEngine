#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <memory>

#ifdef _WIN32
#include <src/platform/windows/Win32Window.h>
#elif __linux__
#include <src/platform/linux/X11Window.h>
#endif

class GameWindow
{
public:
    GameWindow(int width, int height);
    ~GameWindow();

    void Show();
    bool ProcessEvents();

private:
#ifdef _WIN32
    std::unique_ptr<Win32Window> window;
#elif __linux__
    std::unique_ptr<X11Window> window;
#endif
};

#endif // GAMEWINDOW_H
