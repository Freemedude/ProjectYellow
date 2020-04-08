// Program.h

#pragma once

#include "glad/glad.h"

namespace Yellow {
class Shader;


class Program
{
private:
	GLuint _id;

public:
	Program();
	~Program();

	void Attach(Yellow::Shader *shader) const;
	void Bind() const;
	void Link() const;
};

}