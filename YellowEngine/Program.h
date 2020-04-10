// Program.h

#pragma once

#include "glad/glad.h"

namespace Yellow {
struct Mat4;
class Shader;


class Program
{
private:
	GLuint _id;
	GLint GetLocation(const std::string& name);

public:
	Program();
	~Program();

	void Attach(Yellow::Shader *shader) const;
	void Bind() const;
	void Link() const;

	void SetFloat(const std::string& name, float v);
	void SetMatrix(const std::string& name, const Mat4& v);
};

}