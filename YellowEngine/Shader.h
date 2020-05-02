// Shader.h

#pragma once

#include <string>

#include "WindowsWrapper.h"
#include "OpenGLWrapper.h"

namespace Yellow
{
class Shader
{
private:
	wchar_t * _path;
	GLuint _type;
	GLuint _id;

public:
    Shader(wchar_t *path, GLuint type);
    ~Shader();
	GLuint GetId() const;


private:
	void CompileShader();
	static const WCHAR* ShaderTypeToString(GLuint type);
};
}
