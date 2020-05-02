#include "Shader.h"

#include <cassert>
#include <cstdio>


#include "File.h"
#include "OpenGLWrapper.h"

#include "AssetManager.h"


namespace Yellow
{
Shader::Shader(wchar_t *path, GLuint type)
	: _path(path),
	  _type(type)
{
	_id = glCreateShader(type);
	CompileShader();
}

Shader::~Shader()
{
}

GLuint Shader::GetId() const
{   
	return _id;
}

void Shader::CompileShader()
{
	File shaderFile = GetAssetFileByRelativePath(_path);

	GLCall(glShaderSource(_id, 1, &shaderFile.text, nullptr));

	GLCall(glCompileShader(_id));

	// TODO(freemedude 08:25 03-04): Error checking
}

const WCHAR* Shader::ShaderTypeToString(GLuint type)
{
	switch (type)
	{
	case GL_VERTEX_SHADER: return L"Vertex Shader";
	case GL_FRAGMENT_SHADER: return L"Fragment Shader";
	default:
		throw std::invalid_argument("Unsupported shader type");
	}
}
}
