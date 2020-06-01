
Transform CreateTransform()
{
	Transform result {};

	result.scale = {1, 1, 1};

	return result;
}

Mat4 ComputeTransformationMatrix(Transform* transform)
{
	Mat4 translateMatrix = Translate(transform->position);
	Mat4 scaleMatrix = Scale(transform->scale);
	return translateMatrix * scaleMatrix;
}

ShaderProgram CreateShaderProgram(Shader *vs, Shader *fs)
{
	ShaderProgram result;

	result.id = glCreateProgram();
	result.vertex_shader = vs;
	result.fragment_shader = fs;

	return result;
}

Shader CreateShader(char *path, ShaderType type, bool *success)
{
	Shader result {};
	result.id = glCreateShader(type);

	result.type = type;

	// Copy and terminate
	strncpy(result.path, path, MAX_FILE_PATH_LENGTH - 1);
	result.path[MAX_FILE_PATH_LENGTH] = 0;

	bool foundFile = false;
	File shaderFile = AssetManagerGetFile(path, &foundFile);
	assert(foundFile);
	
	glShaderSource(result.id, 1, &shaderFile.text, nullptr);

	glCompileShader(result.id);

	return result;
}

void BindProgram(ShaderProgram* program)
{
	glUseProgram(program->id);
}

void SetUniformMat4(ShaderProgram *program, char* name, Mat4 *matrix)
{
	glGetUniformLocation(program->id, name);
	glUniformMatrix4fv(program->id, 1, false, &matrix->m[0][0]);
}

static void AddAttribute(
    GLuint index,
    GLuint type,
    GLint size,
    GLsizei stride,
    uint64_t offset)
{
	glVertexAttribPointer(
	    index,
	    size,
	    type,
	    GL_FALSE,
	    stride,
	    reinterpret_cast<void*>(offset));

	glEnableVertexAttribArray(index);
}

static void CreateBuffer(
    Array data,
    GLint type,
    GLuint hint,
    GLuint* bufferId,
    const char * label)
{
	glGenBuffers(1, bufferId);
	glBindBuffer(type, *bufferId);
	glObjectLabel(GL_BUFFER, *bufferId, -1, label);

	int bufferSize = data.elementSize * data.count;
	glBufferData( type, static_cast<GLsizeiptr>(bufferSize), data.data, hint);
}


Mesh CreateMesh(Array vertices, Array indices)
{
	Mesh mesh;

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	CreateBuffer(vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW, &mesh.vbo , "Vertex Buffer");
	CreateBuffer(indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, &mesh.ibo, "Index Buffer");

	AddAttribute(0, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, pos));
	AddAttribute(1, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, col));

	return mesh;
}
void BindMesh(Mesh *mesh)
{
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
}

RenderObject CreateRenderObject(Mesh *mesh, Material* material, Transform transform)
{
	RenderObject result;

	result.mesh = mesh;
	result.material = material;
	result.transform = transform;

	return result;
}

void RenderRenderObject(RenderObject* ro)
{
	BindMesh(ro->mesh);
	BindProgram(ro->material->program);

	Mat4 matrix = ComputeTransformationMatrix(&ro->transform);
	SetUniformMat4(ro->material->program, "u_matrix", &matrix);

	glDrawElements(
	    GL_TRIANGLES,
	    static_cast<GLsizei>(ro->mesh->indices.count),
	    GL_UNSIGNED_INT,
	    nullptr);
}

Mesh CreateDemoMeshTriangle()
{
	Mesh mesh;

	Array vertexArray {};
	{
		vertexArray.count = 3;
		vertexArray.elementSize = sizeof(Vertex);
		vertexArray.data = new Vertex[3];

		Vertex verts[] {
			{{ -0.5f, -0.5, 0}, {1, 0, 0}},
			{{0.5, -0.5, 0}, {0, 1, 0}},
			{{0, 0.5, 0}, {0, 0, 1}},
		};
		memcpy(vertexArray.data, verts, sizeof(verts));
	}

	Array indexArray;
	{
		indexArray.data = new Index[3];
		indexArray.count = 3;
		indexArray.elementSize = sizeof(Index);
		
		Index idxs[] {
			0, 1, 2
		};
		memcpy(indexArray.data, idxs, sizeof(idxs));
	}

	return CreateMesh(vertexArray, indexArray);
}
void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
	char buffer[512];
	sprintf(buffer, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	        type, severity, message);

	std::cout << buffer << std::endl;
}

void Initialize()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, nullptr);
}


const char* ShaderTypeToString(GLuint type)
{
	switch (type)
	{
	case GL_VERTEX_SHADER: return "Vertex Shader";
	case GL_FRAGMENT_SHADER: return "Fragment Shader";
	default:
		throw std::invalid_argument("Unsupported shader type");
	}
}

