typedef uint32_t Index;

struct Array
{
	void* data;
	uint64_t count;
	uint64_t elementSize;
};

enum ShaderType
{
	ShaderType_VertexShader = GL_VERTEX_SHADER,
	ShaderType_FragmentShader = GL_FRAGMENT_SHADER
};

struct Shader
{
	char path[MAX_FILE_PATH_LENGTH];
	ShaderType type;
	uint id;
};


/**
 * \param path Path to the shader file
 * \param shaderType Type of shader
 * \param success Success status of shader creation, can be null.
 */
Shader CreateShader(char *path, uint shaderType, bool* success);

void CompileShader(Shader *shader);

const char* ShaderTypeToString(GLuint type);

struct ShaderProgram
{
	uint id;
	Shader *vertex_shader;
	Shader *fragment_shader;
};

ShaderProgram CreateShaderProgram(Shader *vs, Shader *fs);

struct Material
{
	ShaderProgram* program;
};

struct Transform
{
	V3 position;
	V3 scale;

};

Transform CreateTransform();

Mat4 ComputeTransformationMatrix(Transform *transform);

void Initialize();

struct Mesh
{
	Array vertices;
	Array indices;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};

Mesh CreateMesh(Array vertices, Array indices);
void BindMesh(Mesh *mesh);

Mesh CreateDemoMeshTriangle();

struct RenderObject
{
	Transform transform;
	Material* material;
	Mesh* mesh;
};

RenderObject CreateRenderObject(Mesh *mesh, Material* material, Transform transform);
void RenderRenderObject(RenderObject* ro);

struct Scene
{
	RenderObject* objects;
	u32 object_count;
};