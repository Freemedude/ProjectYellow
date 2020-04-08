
#include "WindowsWrapper.h"
#include "OpenGLWrapper.h"
#include "Program.h"
#include "Shader.h"


namespace Yellow
{
Program::Program()
{
	GLCall(_id = glCreateProgram());
}

Program::~Program()
{
	GLCall(glDeleteProgram(_id));
}

void Program::Attach(Shader* shader) const
{
	//Bind();
	GLCall(glAttachShader(_id, shader->GetId()));
}

void Program::Link() const
{
	GLCall(glLinkProgram(_id));
}

void Program::Bind() const
{
	GLCall(glUseProgram(_id));
}

}
