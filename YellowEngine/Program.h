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
	GLint GetLocation(std::string& name);

public:
	Program();
	~Program();

	void Attach(Yellow::Shader *shader) const;
	void Bind() const;
	void Link() const;


	void SetFloat(std::string& name, float v);
	void SetMatrix(std::string& name, Mat4& v);
};

}