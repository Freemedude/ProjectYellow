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

int main(int argc, char* argv[])
{
	using namespace Yellow;
	(argc);
	(argv);

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

	std::string matrixName = "u_matrix";

	Mat4 scale = Scale(0.5, 1, 1);
	Mat4 translate = Translate(1, 1, 0);
	Mat4 modelMatrix = translate * scale;

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

		prog.SetMatrix(matrixName, modelMatrix);

		platform.SwapFrameBuffers();
	}
}
