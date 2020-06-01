#include "win32_yellow.h"

// Third party
#include "glad/glad.c"

#include "asset_manager.cpp"
#include "rendering.cpp"
#include "timers.cpp"
#include "yellow.cpp"

#define Assert(expr) if(!expr) {printf("Assertion failed (" ## __FILE__ ## ", " ## __LINE__ ## ")\n" ## #expr  );} else{}

GameInput g_game_input;

PIXELFORMATDESCRIPTOR
CreateDefaultPixelFormatDescriptor()
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

File ReadFile(const char* path, bool *success)
{
    File result;

    strncpy(result.filename, path, MAX_FILE_PATH_LENGTH);

    HANDLE hTextFile = CreateFileA(
                           path,
                           GENERIC_READ,
                           FILE_SHARE_WRITE,
                           nullptr,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL,
                           nullptr);


    if (hTextFile == INVALID_HANDLE_VALUE)
    {

        UINT err = GetLastError();
        char errorMessage[256];
        sprintf(errorMessage,
                "File not found : %s", result.filename);
        *success = false;
        return result;
    }

    LARGE_INTEGER fileSize;
    GetFileSizeEx(hTextFile, &fileSize);
    result.size_in_bytes = fileSize.QuadPart;

    // Create buffer and null terminate
    result.text = new char[result.size_in_bytes + 1];

    // bytesRead not used.
    DWORD bytesRead;
    ReadFile(hTextFile, result.text, result.size_in_bytes, &bytesRead, nullptr);
    result.text[result.size_in_bytes] = 0;
    CloseHandle(hTextFile);

    *success = true;
    return result;
}

void CreateGLRenderContext(HDC deviceContext)
{
    i32 error = 0;

    HGLRC glRenderContext = wglCreateContext(deviceContext);

    PIXELFORMATDESCRIPTOR pfd = CreateDefaultPixelFormatDescriptor();

    int pixelFormatNumber = ChoosePixelFormat(deviceContext, &pfd);

    bool setFormat = SetPixelFormat(deviceContext, pixelFormatNumber, &pfd);



    wglMakeCurrent(deviceContext, glRenderContext);

    // Set VSync
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)
            wglGetProcAddress("wglSwapIntervalEXT");
    if (wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(0);
    }

    error = GetLastError();
    if (!gladLoadGL())
    {
        printf("Failed to load GLAD\n");
    }

    printf("OpenGL Version: %d.%d\n", GLVersion.major, GLVersion.minor);
}

void KeyboardCB(int32_t keyCode, GameInput* input)
{
    if (keyCode == VK_ESCAPE)
    {
        input->quit = true;
    }
    if (keyCode == VK_F5)
    {
        input->reload_shaders = true;
    }
}

void checkAssetDirectory()
{
    char *assetRootDirectory = GetAssetRootDirectory();
    if (assetRootDirectory)
    {
        printf("Found root asset directory: %s\n", assetRootDirectory);
    } else
    {
        printf("Could not find asset root\n");
    }
}

void CreateExternalConsole(char *title)
{
    FreeConsole();
    bool allocatedConsole = AllocConsole();
    if (allocatedConsole)
    {
        SetConsoleTitleA(title);
        freopen("CONOUT$", "w", stdout);
        FILE *pDummy;
        freopen_s(&pDummy, "CONIN$", "r", stdin);
        freopen_s(&pDummy, "CONOUT$", "w", stderr);
        freopen_s(&pDummy, "CONOUT$", "w", stdout);
    } else
    {
        // Logging
    }
}


inline LRESULT CALLBACK WindowProc(
    _In_ HWND hwnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:

        break;
    case WM_PAINT:
        break;
    case WM_CLOSE:
        return 0;
    case WM_DESTROY:
        return 0;
    }

    return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR arguments,
            int showCode)
{
    // Create window
    WNDCLASSEXA windowClass{};
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = "App";
    windowClass.lpfnWndProc = WindowProc;
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_OWNDC;
    windowClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    if (!RegisterClassExA(&windowClass))
    {
        u16 error = GetLastError();
        printf("Failed to register class: (Error Code: %d)", error);
        return -1;
    }

    HWND hWindow = CreateWindowExA(
                       WS_EX_CLIENTEDGE,
                       "App",
                       "App",
                       WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT,
                       720, 480,
                       nullptr, nullptr, hInstance, nullptr);

    if (!hWindow)
    {
        u16 error = GetLastError();
        printf("Failed to create window: (Error Code: %d)", error);
        return -1;
    }

    HDC hdc = GetDC(hWindow);
    CreateGLRenderContext(hdc);

    ShowWindow(hWindow, showCode);
    UpdateWindow(hWindow);



    checkAssetDirectory();

    GameInitialize();

    int screenWidth = 1500;
    int screenHeight = 1000;
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);


    Timer mainLoopTimer = CreateTimer("Main Loop");
    double secondsPerFrame = 1.0 / 60.0;
    double microsPerFrame = secondsPerFrame * 1000000.0;

    u64 minFrameTimeInMicros = (u64) microsPerFrame;
    u64 totalFrameTime = 0;
    u64 numFrames = 0;
    bool running;
    while (true)
    {
        TimerStart(&mainLoopTimer);
        
        numFrames++;

        MSG msg {};

        while (PeekMessageA(&msg, hWindow, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

#if 0
        if (shouldReloadShaders)
        {
            vShader.CompileShader();
            fShader.CompileShader();
            prog.Link();
            shouldReloadShaders = false;
        }
#endif
        GameUpdateAndRender(&g_game_input);

        u64 frameTimeInMicros = TimerGetTicks(&mainLoopTimer, TimeUnit::MicroSeconds);

        totalFrameTime += frameTimeInMicros;

        u64 frameTimeTargetDifference = minFrameTimeInMicros - frameTimeInMicros;

        if (frameTimeInMicros < minFrameTimeInMicros)
        {
            u64 timeToSleep = frameTimeTargetDifference / 1000 - 1;

            Sleep(timeToSleep);
            frameTimeInMicros = TimerGetTicks(&mainLoopTimer, TimeUnit::MicroSeconds);
        }

        double frameRate = 1.0 / (double) frameTimeInMicros;
        frameRate *= 1000000;

        double frameTime = (double)totalFrameTime / (double)numFrames;
        printf("\rFrame time: (%.1fus/%lluus) - %.1fFPS", frameTime, minFrameTimeInMicros, frameRate);

        wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE);
    }
}
