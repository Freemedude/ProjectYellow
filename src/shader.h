struct Shader
{
	char_t *_path;
	GLuint type;
	GLuint id;
};
    Shader(wchar_t *path, GLuint type);
    ~Shader();
	GLuint GetId() const;

	void CompileShader();

private:
	static const WCHAR* ShaderTypeToString(GLuint type);
};
}
