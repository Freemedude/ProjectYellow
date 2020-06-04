Program::Program(Shader *vertexShader, Shader *fragmentShader)
{
    _vertexShader = vertexShader;
    _fragmentShader = fragmentShader;

	GLCallAssign(_id, glCreateProgram());
    ConstructProgram();
}

Program::~Program()
{
	GLCall(glDeleteProgram(_id));
}

void Program::ConstructProgram()
{
    Attach(_vertexShader);
    Attach(_fragmentShader);
    Link();
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

void Program::SetFloat(const std::string& name, float v)
{
	Bind();
	GLint location = GetLocation(name);
	GLCall(glUniform1fv(location, 1, &v));
}


void Program::SetMatrix(const std::string& name, const Mat4& v)
{
	Bind();
	GLint location = GetLocation(name);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &v.m[0][0]));
}

void Program::Bind() const
{
	GLCall(glUseProgram(_id));
}

GLint Program::GetLocation(const std::string& name)
{
	GLCallAssign(GLuint location, glGetUniformLocation(_id, name.c_str()));
	return location;
}

