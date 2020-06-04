//-------------------------------------------
// Shader
//-------------------------------------------
Shader CreateShader(char *path, ShaderType type, bool *pSuccess)
{
	Shader result {};
	result.id = glCreateShader(type);

	result.type = type;

	// Copy and terminate
	strncpy(result.path, path, MAX_FILE_PATH_LENGTH - 1);
	result.path[MAX_FILE_PATH_LENGTH] = 0;

	bool foundFile = false;
	File shaderFile = AssetManagerGetFile(path, &foundFile);

	if (pSuccess != nullptr)
	{
		*pSuccess = foundFile;
	}

	assert(foundFile);

	glShaderSource(result.id, 1, &shaderFile.text, nullptr);

	// TODO: Handle compile failure
	glCompileShader(result.id);

	return result;
}

const char* ShaderTypeToString(GLuint type)
{
	switch (type)
	{
	case GL_VERTEX_SHADER: return "Vertex Shader";
	case GL_FRAGMENT_SHADER: return "Fragment Shader";
	default:
		return nullptr;
	}
}

//-------------------------------------------
// Shader Program
//-------------------------------------------

ShaderProgram 
CreateShaderProgram(Shader *vs, Shader *fs)
{
	ShaderProgram result {};

	result.vertex_shader = vs;
	result.fragment_shader = fs;
	result.id = glCreateProgram();

	glAttachShader(result.id, vs->id);
	glAttachShader(result.id, fs->id);
	glLinkProgram(result.id);

	return result;
}


void
BindProgram(ShaderProgram* program)
{
	glUseProgram(program->id);
}

void
SetUniformMat4(ShaderProgram *program, char* name, Mat4 *matrix)
{
	int location = glGetUniformLocation(program->id, name);
	glUniformMatrix4fv(location, 1, false, &matrix->m[0][0]);
}

//-------------------------------------------
// Material
//-------------------------------------------

//-------------------------------------------
// Transform
//-------------------------------------------

Transform
CreateTransform()
{
	Transform result {};

	result.scale = {1, 1, 1};

	return result;
}

Mat4
ComputeTransformationMatrix(Transform* transform)
{
	Mat4 translateMatrix = Translate(transform->position);
	Mat4 scaleMatrix = Scale(transform->scale);
	return translateMatrix * scaleMatrix;
}

//-------------------------------------------
// Mesh
//-------------------------------------------
Mesh
CreateMesh(Array vertices, Array indices)
{
	Mesh result {};

	result.vertices = vertices;
	result.indices = indices;

	glGenVertexArrays(1, &result.vao);
	glBindVertexArray(result.vao);

	CreateBuffer(vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW, &result.vbo , "Vertex Buffer");
	CreateBuffer(indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, &result.ibo, "Index Buffer");

	AddAttribute(0, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, pos));
	AddAttribute(1, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, col));

	return result;
}

void
CreateBuffer(
    Array data,
    GLint type,
    GLuint hint,
    GLuint* bufferId,
    const char * label)
{
	glGenBuffers(1, bufferId);
	glBindBuffer(type, *bufferId);
	glObjectLabel(GL_BUFFER, *bufferId, -1, label);

	int bufferSize = data.element_size * data.count;
	glBufferData(type, static_cast<GLsizeiptr>(bufferSize), data.data, hint);
}

void
AddAttribute(
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


void
BindMesh(Mesh *mesh)
{
	glBindVertexArray(mesh->vao);
}

//-------------------------------------------
// Render Object
//-------------------------------------------

RenderObject
CreateRenderObject(Mesh *mesh, Material* material, Transform transform)
{
	RenderObject result {};

	result.mesh = mesh;
	result.material = material;
	result.transform = transform;

	return result;
}

void
RenderRenderObject(RenderObject* ro)
{
	glUseProgram(ro->material->program->id);
	glBindVertexArray(ro->mesh->vao);

	Mat4 matrix = ComputeTransformationMatrix(&ro->transform);
	SetUniformMat4(ro->material->program, "u_matrix", &matrix);

	glDrawElements(
	    GL_TRIANGLES,
	    ro->mesh->indices.count,
	    GL_UNSIGNED_INT,
	    nullptr);
	glBindVertexArray(0);
	glUseProgram(0);
}

Mesh
CreateDemoMeshTriangle()
{
	// Data
	Vertex verts[] {
		{{ -0.5f, -0.5, 0}, {1, 0, 0}},
		{{0.5, -0.5, 0}, {0, 1, 0}},
		{{0, 0.5, 0}, {0, 0, 1}},
	};

	Index idxs[] = {
		0, 1, 2
	};

	// Create destination arrays
	Array vertexArray {ARRAY_COUNT(verts), sizeof(Vertex), new Vertex[3]};
	Array indexArray {ARRAY_COUNT(idxs), sizeof(Index), new Index[3]};

	// Copy vertex data
	memcpy(vertexArray.data, verts, sizeof(verts));
	memcpy(indexArray.data, idxs, sizeof(idxs));

	return CreateMesh(vertexArray, indexArray);
}

void GLAPIENTRY
MessageCallback(
    GLenum source,
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
	printf("%s\n", buffer);

}

