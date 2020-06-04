//-------------------------------------------
// File: rendering.h
// About: Functions and structs related to rendering
// Created by: Freemedude
//-------------------------------------------

// -----------------------------------------//
// Global
// -----------------------------------------//

// TODO: Move this elsewhere
struct Array
{
	u64 count;
	u64 element_size;
	void* data;
};

typedef uint Index;

void 
AddAttribute(
    GLuint index,
    GLuint type,
    GLint size,
    GLsizei stride,
    uint64_t offset);

//------------------------------/
// Shader
//------------------------------/

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

Shader
CreateShader(
    char *path,
    uint shaderType,
    bool* success);

const char*
ShaderTypeToString(GLuint type);

//------------------------------/
// Shader program
//------------------------------/

struct ShaderProgram
{
	uint id;
	Shader *vertex_shader;
	Shader *fragment_shader;
};

ShaderProgram
CreateShaderProgram(Shader *vs, Shader *fs);

void
BindProgram(ShaderProgram* program);

void
BindProgram(ShaderProgram* program);

// ---- Uniforms ----

void
SetUniformMat4(ShaderProgram *program, char* name, Mat4 *matrix);

//------------------------------/
// Material
//------------------------------/

struct Material
{
	ShaderProgram* program;
};

//------------------------------/
// Transform
//------------------------------/

struct Transform
{
	V3 position;
	V3 scale;
};

Transform
CreateTransform();

Mat4
ComputeTransformationMatrix(Transform *transform);

//-------------------------------------------
// Mesh
//-------------------------------------------

struct Mesh
{
	Array vertices;
	Array indices;
	uint vao;
	uint vbo;
	uint ibo;
};

Mesh
CreateMesh(Array vertices, Array indices);

void
BindMesh(Mesh *mesh);

void
CreateBuffer(
    Array data,
    GLint type,
    GLuint hint,
    GLuint* bufferId,
    const char * label);

void 
AddAttribute(
    GLuint index,
    GLuint type,
    GLint size,
    GLsizei stride,
    uint64_t offset);

Mesh
CreateDemoMeshTriangle();

//-------------------------------------------
// Render Object
//-------------------------------------------

struct RenderObject
{
	Transform transform;
	Material* material;
	Mesh* mesh;
};

RenderObject
CreateRenderObject(
    Mesh *mesh,
    Material* material,
    Transform transform);

void
RenderRenderObject(RenderObject* ro);

//-------------------------------------------
// Scene
//-------------------------------------------

struct Scene
{
	RenderObject* objects;
	u32 object_count;
};