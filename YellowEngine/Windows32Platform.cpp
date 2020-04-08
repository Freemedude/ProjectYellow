#include "Windows32Platform.h"

#include <cstdio>

#include <glad/glad.h>


inline LRESULT CALLBACK WindowProc(
	_In_ HWND hwnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

namespace Yellow
{
OnKeyCallback* s_onKeyCallback;

Yellow::Windows32Platform::Windows32Platform(
	int width, 
	int height,
	std::wstring& title)
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


void Windows32Platform::Quit()
{
	_shouldQuit = true;
}

bool Yellow::Windows32Platform::ProcessMessages()
{
	if (_shouldQuit)
	{
		return false;
	}
	while (PeekMessage(&_message, _hWindow, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&_message);
		DispatchMessage(&_message);

		if (_message.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

void Yellow::Windows32Platform::SwapFrameBuffers() const
{
	wglSwapLayerBuffers(_hDeviceContext, WGL_SWAP_MAIN_PLANE);
}

void Yellow::Windows32Platform::InitializeOpenGLContext()
{
	PIXELFORMATDESCRIPTOR pfd = CreateDefaultPixelFormatDescriptor();

	int pixelFormatNumber = ChoosePixelFormat(_hDeviceContext, &pfd);

	SetPixelFormat(_hDeviceContext, pixelFormatNumber, &pfd);

	_hOpenGLRenderContext = wglCreateContext(_hDeviceContext);

	wglMakeCurrent(_hDeviceContext, _hOpenGLRenderContext);

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
	pfd.cColorBits = 32;
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
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.bReserved = 0;
	pfd.dwLayerMask = 0;
	pfd.dwVisibleMask = 0;
	pfd.dwDamageMask = 0;
	return pfd;
}
}


inline LRESULT CALLBACK WindowProc(
	_In_ HWND hwnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	if (uMsg == WM_KEYDOWN)
	{
		Yellow::s_onKeyCallback(wParam);
	}

	return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}
