namespace Yellow {
class Program
{
private:
	GLuint _id;
    Shader *_vertexShader = nullptr;
    Shader *_fragmentShader = nullptr;

	GLint GetLocation(const std::string& name);
	void Attach(Yellow::Shader *shader) const;

public:
    Program(Shader *vertexShader, Shader *fragmentShader);
    ~Program();

    void ConstructProgram();
	void Bind() const;
	void Link() const;

	void SetFloat(const std::string& name, float v);
	void SetMatrix(const std::string& name, const Mat4& v);
};

}