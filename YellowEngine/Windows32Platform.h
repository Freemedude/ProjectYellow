// Windows32Platform.h

#pragma once

#include <string>

#include "WindowsWrapper.h"
#include "OpenGLWrapper.h"


namespace Yellow
{
typedef void (OnKeyCallback)(UINT);


class Windows32Platform
{
private:
	HDC _hDeviceContext;
	HWND _hWindow;
	HGLRC _hOpenGLRenderContext;
	HINSTANCE _hInstance;
	MSG _message;
	bool _shouldQuit;

public:
	Windows32Platform(int width, int height, std::wstring& title);
	~Windows32Platform();


	void SetOnKeyCallback(OnKeyCallback cb);
	bool ProcessMessages();
	void SwapFrameBuffers() const;
	void Quit();
private:
	void InitializeOpenGLContext();

	// Create default pixel format descriptor
	static PIXELFORMATDESCRIPTOR
	CreateDefaultPixelFormatDescriptor();
};
}
