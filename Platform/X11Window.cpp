#ifdef __linux__
#include "X11Window.h"
#include "../Resources/GameManager.h"

#include <iostream>

X11Window::X11Window(int width, int height)
{
    GameManager::display = XOpenDisplay(nullptr);
    if (!GameManager::display)
    {
        throw std::runtime_error("Cannot open display.");
    }

    int screen = DefaultScreen(GameManager::display);
    ::Window root = RootWindow(GameManager::display, screen);

    XSetWindowAttributes attrs = {};
    attrs.background_pixel = WhitePixel(GameManager::display, screen);
    attrs.border_pixel = BlackPixel(GameManager::display, screen);
    attrs.event_mask = ExposureMask | KeyPressMask;

    GameManager::window = XCreateWindow(
        GameManager::display,
        root,
        100, 100, width, height, 1,
        DefaultDepth(GameManager::display, screen),
        InputOutput,
        DefaultVisual(GameManager::display, screen),
        CWBackPixel | CWBorderPixel | CWEventMask,
        &attrs);

    XMapWindow(GameManager::display, GameManager::window);
    XStoreName(GameManager::display, GameManager::window, "Hello, Linux!");
}

X11Window::~X11Window()
{
    XDestroyWindow(GameManager::display, GameManager::window);
    XCloseDisplay(GameManager::display);
}

/*
void X11Window::Show()
{
    XMapWindow(display, window);
}
*/

bool X11Window::ProcessEvents()
{
    XEvent event;
    while (XPending(GameManager::display))
    {
        XNextEvent(GameManager::display, &event);

        if (event.type == ClientMessage)
        {
            Atom wmDelete = XInternAtom(GameManager::display, "WM_DELETE_WINDOW", False);
            if (event.xclient.data.l[0] == static_cast<long>(wmDelete))
            {
                return false;
            }
        }

        if (event.type == KeyPress)
        {
            return false;
        }
    }
    return true;
}
#endif
