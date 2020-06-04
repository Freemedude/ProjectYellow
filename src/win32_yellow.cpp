#include "win32_yellow.h"

// Third party
#include "glad/glad.c"

#include "asset_manager.cpp"
#include "rendering.cpp"
#include "timers.cpp"
#include "yellow.cpp"

#define Assert(expr) if(!expr) {printf("Assertion failed (" ## __FILE__ ## ", " ## __LINE__ ## ")\n" ## #expr  );} else{}

GameInput g_game_input;

const char* g_appname = "Project Yellow";
bool g_running = true;

PIXELFORMATDESCRIPTOR
CreateDefaultPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    return pfd;
}

File
ReadFile(const char* path, bool *success)
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

void
CreateGLRenderContext(HDC deviceContext)
{
    i32 error = 0;

    PIXELFORMATDESCRIPTOR pfd = CreateDefaultPixelFormatDescriptor();

    int pixelFormatNumber = ChoosePixelFormat(deviceContext, &pfd);

    bool setFormat = SetPixelFormat(deviceContext, pixelFormatNumber, &pfd);

    HGLRC glRenderContext = wglCreateContext(deviceContext);

    bool madeCurrent = wglMakeCurrent(deviceContext, glRenderContext);

    if (!gladLoadGL())
    {
        printf("Failed to load GLAD\n");
    }

    // Set VSync
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)
            wglGetProcAddress("wglSwapIntervalEXT");
    if (wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(0);
    }


    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);

    printf("OpenGL Version: %d.%d\n", GLVersion.major, GLVersion.minor);
}

void
KeyboardCB(int32_t keyCode, GameInput* input)
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

void
CheckAssetDirectory()
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

LRESULT CALLBACK 
WindowProc(
    _In_ HWND hwnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
    case WM_DESTROY:
        g_running = true;
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void 
CreateExternalConsole(const char *title)
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

int CALLBACK
WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR arguments,
    int showCode)
{
    CreateExternalConsole(g_appname);
    // Create window
    WNDCLASSEXA windowClass{};
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = g_appname;
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
                       g_appname,
                       g_appname,
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

    CheckAssetDirectory();

    ShowWindow(hWindow, showCode);
    UpdateWindow(hWindow);

    HDC hdc = GetDC(hWindow);

    CreateGLRenderContext(hdc);


    GameInitialize();

    int screenWidth = 1500;
    int screenHeight = 1000;
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

#if 0
    Timer mainLoopTimer = CreateTimer("Main Loop");
    double secondsPerFrame = 1.0 / 60.0;
    double microsPerFrame = secondsPerFrame * 1000000.0;

    u64 minFrameTimeInMicros = (u64) microsPerFrame;
    u64 totalFrameTime = 0;
    u64 numFrames = 0;
    bool running;
#endif
    while (g_running)
    {
        //TimerStart(&mainLoopTimer);

        //numFrames++;

        MSG msg {};

        while (PeekMessageA(&msg, hWindow, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        GameUpdateAndRender(&g_game_input);

        wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE);
#if 0

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
#endif

    }
    return 0;
}
