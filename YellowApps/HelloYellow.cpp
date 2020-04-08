#include "HelloYellow.h"

// System
#include <string>

// Engine
#include "YellowEngine.h"


bool shouldQuit = false;

void KeyboardCB(uint32_t keyCode)
{
	if (keyCode == VK_ESCAPE)
	{
		shouldQuit = true;
	}
}

void TestMath()
{
	using namespace Yellow;

	Mat4 id = Identity();

	Mat4 trans = Translate(1, 0, 1);
	Mat4 invTrans = Translate(-1, 0, -1);
	Mat4 scale = Scale(1, 0.5, 2);
	Mat4 invScale = Scale(1, 2, 0.5);

	Mat4 alsoId = id * id;

	Mat4 result = trans * invTrans;

}

int main(int argc, char* argv[])
{
	(argc);
	(argv);
	using namespace Yellow;
	TestMath();
	std::wstring appName = L"My App";
	Windows32Platform platform(1000, 1000, appName);
	platform.SetOnKeyCallback(KeyboardCB);

	std::string vertexShaderPath = "../assets/shaders/OnlyPosition.vert";
	Shader vShader(vertexShaderPath, GL_VERTEX_SHADER);

	std::string fragmentShaderPath = "../assets/shaders/ColorPosition.frag";
	Shader fShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	Program prog;
	prog.Attach(&vShader);
	prog.Attach(&fShader);
	prog.Link();

	RenderObject triangle = RenderObject::Triangle();

	float redIncrement = 0.001f;

	float red = 0;
	while (platform.ProcessMessages())
	{
		if (shouldQuit)
		{
			platform.Quit();
		}

		red = fmod(red + redIncrement, 1);
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glClearColor(red, 0, 0, 0));

		prog.Bind();
		triangle.Render();

		platform.SwapFrameBuffers();
	}
}
