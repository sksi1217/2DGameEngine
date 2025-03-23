#ifdef _WIN32
#include "Win32Window.h"

Win32Window::Win32Window(int width, int height)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "MyWindowClass";

    if (!RegisterClass(&wc))
    {
        throw std::runtime_error("Failed to register window class.");
    }

    hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "Hello, Windows!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

    if (!hwnd)
    {
        throw std::runtime_error("Failed to create window.");
    }
}

Win32Window::~Win32Window()
{
    DestroyWindow(hwnd);
}

void Win32Window::Show()
{
    ShowWindow(hwnd, SW_SHOW);
}

bool Win32Window::ProcessEvents()
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
        {
            return false;
        }
    }
    return true;
}

HWND Win32Window::GetHandle() const
{
    return hwnd;
}
#endif
