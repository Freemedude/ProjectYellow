#include "win32_yellow.h"

// Third party
#include "glad/glad.c"

// Unity build
#include "asset_manager.cpp"
#include "file.cpp"
#include "program.cpp"
#include "rendering.cpp"
#include "scene.cpp"
#include "shader.cpp"
#include "timers.cpp"
#include "win32_platform.cpp"

bool shouldQuit = false;
bool shouldReloadShaders = false;

void KeyboardCB(int32_t keyCode)
{
    if (keyCode == VK_ESCAPE)
    {
        shouldQuit = true;
    }
    // Reload shaders
    if (keyCode == VK_F5)
    {
        shouldReloadShaders = true;
    }
}

static Yellow::Scene scene;
static Yellow::Windows32Platform *platform;

void MoveObjectBackAndForth(Yellow::RenderObject *ro)
{
    Yellow::V3 *pos = &ro->transform->position;
    static float moveObjectDelta = 0.001;
    pos->m[0] += moveObjectDelta;

    if (pos->m[0] < -0.5 || pos->m[0] > 0.5)
    {
        moveObjectDelta *= -1;
    }
}

void SwapBuffers()
{
    platform->SwapFrameBuffers();
}

void Render()
{
    GLCall(glClearColor(0.5, 0.2, 0.2, 0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    for (auto &ro : scene.RenderObjects())
    {
        ro->Render();
    }

    SwapBuffers();
}

void checkAssetDirectory()
{
    wchar_t *assetRootDirectory = Yellow::GetAssetRootDirectory();
    if (assetRootDirectory)
    {
        printf("Found root asset directory: %ws\n", assetRootDirectory);
    } else
    {
        printf("Could not find asset root\n");
    }
}


int main(int argc, char *argv[])
{
    using namespace Yellow;
    (argc);
    (argv);

    platform = new Windows32Platform(1000, 1000, L"My App");
    platform->SetOnKeyCallback(KeyboardCB);
    platform->SetOnWMPaintCallback(Render);
    platform->CreateExternalConsole("HelloYellow Console!");

    checkAssetDirectory();


    Yellow::Initialize();


    int screenWidth = 1500;
    int screenHeight = 1000;
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);


    Shader vShader(L"shaders/OnlyPosition.vert", GL_VERTEX_SHADER);
    Shader fShader(L"shaders/ColorPosition.frag", GL_FRAGMENT_SHADER);
    Program prog(&vShader, &fShader);

    RenderObject objects[2];

    RenderObject imported = ImportModelOBJ(L"models/test.obj");

    Material material{};
    material.program = &prog;
    Mesh *triangleMesh = Mesh::Triangle();
    Transform transforms[2];

    // Fill scene
    {
        objects[0].Create(triangleMesh, &material,
                          &transforms[0]);
        objects[0].transform->position = {0.5, 0, 0};
        objects[0].transform->scale = {aspectRatio, 1, 1};
        scene.RenderObjects().push_back(&objects[0]);
    }
    {
        objects[1].Create(triangleMesh, &material,
                          &transforms[1]);
        objects[1].transform->position = {-0.5, 0.25, 0};
        scene.RenderObjects().push_back(&objects[1]);
    }

    Timer mainLoopTimer("Main Loop");
    double secondsPerFrame = 1.0 / 60.0;
    double microsPerFrame = secondsPerFrame * 1000000.0;

    u64 minFrameTimeInMicros = (u64) microsPerFrame;
    u64 totalFrameTime = 0;
    u64 numFrames = 0;
    while (true)
    {
        mainLoopTimer.Start();

        numFrames++;

        {
            if (!platform->ProcessMessages())
            {
                break;
            }
        }

        if (shouldQuit)
        {
            platform->Quit();
        }

        if (shouldReloadShaders)
        {
            vShader.CompileShader();
            fShader.CompileShader();
            prog.Link();
            shouldReloadShaders = false;
        }

        MoveObjectBackAndForth(scene.RenderObjects()[1]);

        Render();

        u64 frameTimeInMicros = mainLoopTimer.GetTicksInUnit(TimeUnit::MicroSeconds);

        totalFrameTime += frameTimeInMicros;

        u64 frameTimeTargetDifference = minFrameTimeInMicros - frameTimeInMicros;

        if (frameTimeInMicros < minFrameTimeInMicros)
        {
            u64 timeToSleep = frameTimeTargetDifference / 1000 - 1;

            std::cout << "Sleeping for " << timeToSleep << "ms" << std::endl;
            Sleep(timeToSleep);
            frameTimeInMicros = mainLoopTimer.GetTicksInUnit(TimeUnit::MicroSeconds);
        }

        double frameRate = 1.0 / (double) frameTimeInMicros;
        frameRate *= 1000000;

        std::cout << "FrameTime ("
                  << totalFrameTime / numFrames << "/" << minFrameTimeInMicros << "us) - "
                  << frameRate << "FPS"
                  << std::endl;
    }
}
