// Windows32Platform.h

#pragma once

#include <string>

#include "OpenGLWrapper.h"
#include "WindowsWrapper.h"

namespace Yellow
{
typedef void(OnKeyCallback)(INT);
typedef void(OnWMPaintCallback)();

class Windows32Platform
{
private:
    HDC _hDeviceContext;
    HWND _hWindow;
    HGLRC _hOpenGLRenderContext;
    HINSTANCE _hInstance;
    MSG _message;

public:
    Windows32Platform(int width, int height, const std::wstring &title);
    ~Windows32Platform();

    void SetOnKeyCallback(OnKeyCallback cb);
    void SetOnWMPaintCallback(OnWMPaintCallback cb);
    void CreateExternalConsole(char *title);

    bool ProcessMessages();
    void SwapFrameBuffers() const;

    void Quit();

private:
    void InitializeOpenGLContext();

    // Create default pixel format descriptor
    static PIXELFORMATDESCRIPTOR
    CreateDefaultPixelFormatDescriptor();
};
} // namespace Yellow
