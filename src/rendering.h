namespace Yellow
{

typedef uint32_t Index;

struct Array
{
	void* data;
	uint64_t count;
	uint64_t elementSize;
};

class Material
{
public:
	Program* program;
};

class Transform
{
public:
	V3 position = {0, 0, 0};
	V3 scale = {1, 1, 1};

	Mat4 ComputeMatrix() const;
};

void Initialize();

class Mesh
{
public:
	Array vertices;
	Array indices;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	Mesh(Array vertices,
	     Array indices);


	static Mesh* Triangle();


	void Bind() const;
private:
	static void AddAttribute(
	    GLuint index,
	    GLuint type,
	    GLint size,
	    GLsizei stride,
	    uint64_t offset);
	static void CreateBuffer(Array data, GLint type, GLuint hint,
	                         GLuint* bufferId, const char * label);
};

class RenderObject
{
public:
	Transform* transform;
	Material* material;
	Mesh* mesh;

	RenderObject();
	~RenderObject();

	void Create(Mesh *mesh, Material *material, Transform *transform);

	void Render() const;
};
}
