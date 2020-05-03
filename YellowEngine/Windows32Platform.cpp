#include "Windows32Platform.h"

// System
#include <cstdio>
#include <iostream>

// External
#include <glad/glad.h>

inline LRESULT CALLBACK WindowProc(
    _In_ HWND hwnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

bool g_shouldQuit = false;

namespace Yellow
{
// todo: Make these not global
// Callbacks
static OnKeyCallback *s_onKeyCallback;
static OnWMPaintCallback *s_onWMPaintCallback;

Windows32Platform::Windows32Platform(
    int width,
    int height,
    const std::wstring &title)
{
    _hInstance = GetModuleHandle(nullptr);
    WNDCLASSEX windowClass{};
    windowClass.hInstance = _hInstance;
    windowClass.lpszClassName = title.c_str();
    windowClass.lpfnWndProc = WindowProc;
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_OWNDC;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassEx(&windowClass))
    {
        printf("Failed to register class\n");
    }

    _hWindow = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        title.c_str(),
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        nullptr, nullptr, _hInstance, nullptr);

    if (!_hWindow)
    {
        printf("Failed to create window\n");
    }
    UINT lastError = GetLastError();

    _hDeviceContext = GetDC(_hWindow);

    ShowWindow(_hWindow, SW_SHOWNORMAL);
    UpdateWindow(_hWindow);

    InitializeOpenGLContext();
}

Windows32Platform::~Windows32Platform()
{
    DestroyWindow(_hWindow);
}

void Windows32Platform::SetOnKeyCallback(OnKeyCallback cb)
{
    s_onKeyCallback = cb;
}

void Windows32Platform::SetOnWMPaintCallback(OnWMPaintCallback cb)
{
    s_onWMPaintCallback = cb;
}

void Windows32Platform::Quit()
{
    g_shouldQuit = true;
}

bool Windows32Platform::ProcessMessages()
{
    if (g_shouldQuit)
    {
        return false;
    }
    while (PeekMessage(&_message, _hWindow, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&_message);
        DispatchMessage(&_message);

    }
    return true;
}

void Yellow::Windows32Platform::SwapFrameBuffers() const
{
    wglSwapLayerBuffers(_hDeviceContext, WGL_SWAP_MAIN_PLANE);
}

void Yellow::Windows32Platform::InitializeOpenGLContext()
{
    UINT lastError = GetLastError();
    PIXELFORMATDESCRIPTOR pfd = CreateDefaultPixelFormatDescriptor();

    int pixelFormatNumber = ChoosePixelFormat(_hDeviceContext, &pfd);
    lastError = GetLastError();

    bool setFormat = SetPixelFormat(_hDeviceContext, pixelFormatNumber, &pfd);
    lastError = GetLastError();

    _hOpenGLRenderContext = wglCreateContext(_hDeviceContext);
    lastError = GetLastError();

    wglMakeCurrent(_hDeviceContext, _hOpenGLRenderContext);
    lastError = GetLastError();
    if (!gladLoadGL())
    {
        printf("Failed to load GLAD\n");
    }

    printf("OpenGL Version: %d.%d\n", GLVersion.major, GLVersion.minor);
}

PIXELFORMATDESCRIPTOR
Yellow::Windows32Platform::CreateDefaultPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1; // Must be one
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cRedBits = 0;
    pfd.cRedShift = 0;
    pfd.cGreenBits = 0;
    pfd.cGreenShift = 0;
    pfd.cBlueBits = 0;
    pfd.cBlueShift = 0;
    pfd.cAlphaBits = 0;
    pfd.cAlphaShift = 0;
    pfd.cAccumBits = 0;
    pfd.cAccumRedBits = 0;
    pfd.cAccumGreenBits = 0;
    pfd.cAccumBlueBits = 0;
    pfd.cAccumAlphaBits = 0;
    pfd.cDepthBits = 32;
    pfd.cStencilBits = 0;
    pfd.cAuxBuffers = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.bReserved = 0;
    pfd.dwLayerMask = 0;
    pfd.dwVisibleMask = 0;
    pfd.dwDamageMask = 0;
    return pfd;
}

void Windows32Platform::CreateExternalConsole(char *title)
{
        FreeConsole();
    bool allocatedConsole = AllocConsole();
    if(allocatedConsole)
    {
        SetConsoleTitleA(title);
        freopen("CONOUT$", "w", stdout);
        FILE *pDummy;
        freopen_s(&pDummy, "CONIN$", "r", stdin);
        freopen_s(&pDummy, "CONOUT$", "w", stderr);
        freopen_s(&pDummy, "CONOUT$", "w", stdout);
    }
    else
    {
        // Logging
    }
}

} // namespace Yellow

inline LRESULT CALLBACK WindowProc(
    _In_ HWND hwnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:

        if (Yellow::s_onKeyCallback)
            Yellow::s_onKeyCallback(wParam);
        break;
    case WM_PAINT:
        if (Yellow::s_onWMPaintCallback)
            Yellow::s_onWMPaintCallback();
        break;
    case WM_CLOSE:
        g_shouldQuit = true;
        return 0;
    case WM_DESTROY:
        g_shouldQuit = true;
        return 0;
    }

    return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}
