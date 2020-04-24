﻿// Shader.h

#pragma once

#include <string>

#include "WindowsWrapper.h"
#include "OpenGLWrapper.h"

namespace Yellow
{
class Shader
{
private:
	const std::string& _path;
	GLuint _type;
	GLuint _id;

public:
	Shader(const std::string& path, GLuint type);
	~Shader();
	GLuint GetId() const;


private:
	void CompileShader();
	static const WCHAR* ShaderTypeToString(GLuint type);
};
}
