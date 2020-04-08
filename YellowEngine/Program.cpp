
#include "WindowsWrapper.h"
#include "OpenGLWrapper.h"
#include "YellowMath.h"
#include "Program.h"
#include "Shader.h"


namespace Yellow
{


Program::Program()
{
	GLCallAssign(_id, glCreateProgram());
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

void Program::SetFloat(std::string& name, float v)
{
	Bind();
	GLint location = GetLocation(name);
	glUniform1fv(location, 1, &v);
}


void Program::SetMatrix(std::string& name, Mat4& v)
{
	Bind();
	GLint location = GetLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &v.m[0][0]);
}

void Program::Bind() const
{
	GLCall(glUseProgram(_id));
}

GLint Program::GetLocation(std::string& name)
{
	GLCallAssign(GLuint location, glGetUniformLocation(_id, name.c_str()));
	return location;
}

}
