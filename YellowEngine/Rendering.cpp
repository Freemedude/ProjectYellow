#include "Rendering.h"

#include "YellowEngine.h"
#include "YellowMath.h"


namespace Yellow
{
Mat4 Transform::ComputeMatrix() const
{
	Mat4 translateMatrix = Translate(position);
	Mat4 scaleMatrix = Scale(scale);
	return translateMatrix * scaleMatrix;
}


Mesh::Mesh(Array vertices, Array indices)
	: vertices(vertices), indices(indices)
{
	GLCall(glGenVertexArrays(1, &vao));

	Bind();

	CreateBuffer(vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW, &vbo);
	CreateBuffer(indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,
	             &ibo);

	AddAttribute(0, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, pos));
	AddAttribute(1, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, col));
}

void Mesh::AddAttribute(
	GLuint index,
	GLuint type,
	GLint size,
	GLsizei stride,
	uint32_t offset)
{
	GLCall(glVertexAttribPointer(
		index,
		size,
		type,
		GL_FALSE,
		stride,
		reinterpret_cast<void*>(offset)));

	GLCall(glEnableVertexAttribArray(index));
}

void Mesh::CreateBuffer(Array data, GLint type, GLuint hint,
                        OUT GLuint* bufferId)
{
	GLCall(glGenBuffers(1, bufferId));
	GLCall(glBindBuffer(type, *bufferId));
	GLCall(glBufferData(
		type,
		static_cast<GLsizeiptr>(data.elementSize * data.count * data.elementSize
		),
		data.data,
		hint));
}

void Mesh::Bind() const
{
	GLCall(glBindVertexArray(vao));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
}

RenderObject::RenderObject(Mesh* mesh, Material* material, Transform* transform)
	: mesh(mesh), material(material), transform(transform)
{
}

RenderObject::~RenderObject()
{
}


void RenderObject::Render() const
{
	mesh->Bind();
	material->program->Bind();
	material->program->SetMatrix("u_matrix", transform->ComputeMatrix());

	GLCall(glDrawElements(
		GL_TRIANGLES,
		static_cast<GLsizei>(mesh->indices.count),
		GL_UNSIGNED_INT,
		nullptr));
}

Mesh* Mesh::Triangle()
{
	Vertex* vertices = new Vertex[3];
	{
		Vertex verts[]{
			{{-0.5f, -0.5, 0}, {1, 0, 0}},
			{{0.5, -0.5, 0}, {0, 1, 0}},
			{{0, 0.5, 0}, {0, 0, 1}},
		};
		memcpy(vertices, verts, sizeof(verts));
	}

	Index* indices = new Index[3];
	{
		Index idxs[]{
			0, 1, 2
		};
		memcpy(indices, idxs, sizeof(idxs));
	}

	return new Mesh{{vertices, 3, sizeof(Vertex)}, {indices, 3, sizeof(Index)}};
}
}
