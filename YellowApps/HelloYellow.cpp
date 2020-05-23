#include "HelloYellow.h"

// System
#include <iostream>
#include <stdio.h>
#include <string>

// Engine
#include "AssetManager.h"
#include "Rendering.h"
#include "Scene.h"
#include "YellowEngine.h"
#include "Timers.h"

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

    Timer globalTimer("Global timer");
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
    while (true)
    {

        mainLoopTimer.Start();
        {
            ScopedTimer winMessagesTimer("Windows Messages");
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

        // Frame end timings
        mainLoopTimer.Stop();

        u64 deltaTimeMillis = mainLoopTimer.GetTicksInUnit(TimeUnit::MilliSeconds);
        double deltaTimeSeconds = deltaTimeMillis / 1000.0;

        int frameRate = (int) (1.0 / deltaTimeSeconds);

        int totalTimeInSeconds = (int) globalTimer.GetTicksInUnit(TimeUnit::Seconds);
        printf("Total: %ds - %llums %dFPS \n",
               totalTimeInSeconds,
               deltaTimeMillis,
               frameRate);
    }
}
