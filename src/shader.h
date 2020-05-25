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

	void CompileShader();

private:
	static const WCHAR* ShaderTypeToString(GLuint type);
};
}
