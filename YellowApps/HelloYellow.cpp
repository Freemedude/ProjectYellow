#include "HelloYellow.h"

// System
#include <string>

// Engine
#include "Scene.h"
#include "YellowEngine.h"


bool shouldQuit = false;

void KeyboardCB(uint32_t keyCode)
{
	if (keyCode == VK_ESCAPE)
	{
		shouldQuit = true;
	}
}

int main(int argc, char* argv[])
{
	using namespace Yellow;
	(argc);
	(argv);

	std::wstring appName = L"My App";
	Windows32Platform platform(1000, 1000, appName);
	platform.SetOnKeyCallback(KeyboardCB);

	Scene scene;

	std::string vertexShaderPath = "../assets/shaders/OnlyPosition.vert";
	Shader vShader(vertexShaderPath, GL_VERTEX_SHADER);

	std::string fragmentShaderPath = "../assets/shaders/ColorPosition.frag";
	Shader fShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	Program prog;
	prog.Attach(&vShader);
	prog.Attach(&fShader);
	prog.Link();

	Material basic;
	basic.program = &prog;

	Transform transforms[2];
	
	// Fill scene
	{
		RenderObject* ro = RenderObject::Triangle();
		ro->material = &basic;
		ro->transform = &transforms[0];
		ro->transform->position = { 0.5,0,0 };
		scene.RenderObjects().push_back(ro);
	}
	{
		RenderObject* ro = RenderObject::Triangle();
		ro->material = &basic;
		ro->transform = &transforms[1];
		ro->transform->position = { -0.5,0.25,0 };
		scene.RenderObjects().push_back(ro);
	}


	prog.Bind();
	while (platform.ProcessMessages())
	{
		if (shouldQuit)
		{
			platform.Quit();
		}

		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glClearColor(0.5, 0.2, 0.2, 0));

		prog.Bind();
		for (auto& ro : scene.RenderObjects())
		{
			ro->Render();
		}


		platform.SwapFrameBuffers();
	}
}
