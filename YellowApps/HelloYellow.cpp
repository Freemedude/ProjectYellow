#include "HelloYellow.h"

// System
#include <iostream>
#include <stdio.h>
#include <string>

// Engine
#include "Rendering.h"
#include "Scene.h"
#include "YellowEngine.h"

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
    static float moveObjectDelta = 0.01;
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

int main(int argc, char *argv[])
{
    using namespace Yellow;
    (argc);
    (argv);

    SetCurrentDirectory(L"D:\\Projects\\ProjectYellow\\build\\YellowApps\\Debug");

    int screenWidth = 1500;
    int screenHeight = 1000;
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    platform = new Windows32Platform(1000, 1000, L"My App");
    Yellow::Initialize();
    platform->SetOnKeyCallback(KeyboardCB);
    platform->SetOnWMPaintCallback(Render);

    platform->CreateExternalConsole("HelloYellow Console!");

    Shader vShader(L"shaders/OnlyPosition.vert", GL_VERTEX_SHADER);

    Shader fShader(L"shaders/ColorPosition.frag", GL_FRAGMENT_SHADER);

    Program prog(&vShader, &fShader);

    Material material{};
    material.program = &prog;
    Mesh *triangleMesh = Mesh::Triangle();
    Transform transforms[2];

    // Fill scene
    {
        RenderObject *ro = new RenderObject(triangleMesh, &material,
                                            &transforms[0]);
        ro->transform->position = {0.5, 0, 0};
        ro->transform->scale = {aspectRatio, 1, 1};
        scene.RenderObjects().push_back(ro);
    }
    {
        RenderObject *ro = new RenderObject(triangleMesh, &material,
                                            &transforms[1]);
        ro->transform->position = {-0.5, 0.25, 0};
        scene.RenderObjects().push_back(ro);
    }

    while (platform->ProcessMessages())
    {
        if (shouldReloadShaders)
        {
            vShader.CompileShader();
            fShader.CompileShader();
            prog.Link();
            shouldReloadShaders = false;
        }

        if (shouldQuit)
        {
            platform->Quit();
        }

        MoveObjectBackAndForth(scene.RenderObjects()[1]);

        Render();
    }
}
