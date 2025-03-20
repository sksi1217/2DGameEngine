#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#ifdef _WIN32
#include <windows.h>

class Win32Window
{
public:
    Win32Window(int width, int height);
    ~Win32Window();

    void Show();
    bool ProcessEvents();
    HWND GetHandle() const;

private:
    HWND hwnd;
};
#endif

#endif // WIN32_WINDOW_H
