#include "Rendering.h"

#include "YellowEngine.h"
#include "YellowMath.h"

namespace Yellow
{


RenderObject::RenderObject(ArrayPtr<Vertex> vertices,
                           ArrayPtr<Index> indices)
{
	this->vertices = vertices;
	this->indices = indices;

	GLCall(glGenVertexArrays(1, &vao));

	Bind();

	CreateBuffer(vertices.ToVoidPtr(), GL_ARRAY_BUFFER, GL_STATIC_DRAW, &vbo);
	CreateBuffer(indices.ToVoidPtr(), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, &ibo);

	AddAttribute(0, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, pos));
	AddAttribute(1, GL_FLOAT, 3, sizeof(Vertex), offsetof(Vertex, col));
}

void RenderObject::AddAttribute(
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

void RenderObject::CreateBuffer(ArrayVoidPtr data, GLint type, GLuint hint, OUT GLuint *bufferId)
{

	GLCall(glGenBuffers(1, bufferId));
	GLCall(glBindBuffer(type, *bufferId));
	GLCall(glBufferData(
		type,
		data.elementSize * data.count,
		data.data,
		hint));
}

RenderObject::~RenderObject()
{
	GLCall(glDeleteVertexArrays(1, &vao));
}

void RenderObject::Bind() const
{
	GLCall(glBindVertexArray(vao));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
}

void RenderObject::Render() const
{
	Bind();
	GLCall(glDrawElements(GL_TRIANGLES, indices.count, GL_UNSIGNED_INT, nullptr));
}

RenderObject RenderObject::Triangle()
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

	return {{vertices, 3}, {indices, 3}};
}
}
