#ifndef X11_WINDOW_H
#define X11_WINDOW_H

#ifdef __linux__
#include <X11/Xlib.h>

class X11Window
{
public:
    X11Window(int width, int height);
    ~X11Window();

    bool ProcessEvents();

private:
    // Запрещаем копирование и присваивание
    X11Window(const X11Window &) = delete;
    X11Window &operator=(const X11Window &) = delete;
};
#endif

#endif // X11_WINDOW_H
