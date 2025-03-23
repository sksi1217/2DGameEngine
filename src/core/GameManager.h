#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <X11/Xlib.h>

class GameManager
{
public:
#ifdef _WIN32

#elif __linux__
    static Display *display;
    static ::Window window;
#endif
};

#endif
