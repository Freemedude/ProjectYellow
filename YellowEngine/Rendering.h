// Rendering.h

#pragma once

// System
#include <cstdint>

#include "WindowsWrapper.h"
#include "OpenGLWrapper.h"
#include "YellowMath.h"
#include "Shader.h"
#include "Program.h"

namespace Yellow
{

struct ArrayVoidPtr
{
	void* data;
	uint64_t count;
	uint64_t elementSize;
};

typedef uint32_t Index;

template <class T>
class ArrayPtr
{
public:
	T* data;
	uint64_t count;

	ArrayVoidPtr ToVoidPtr()
	{
		return {data, count, sizeof(data[0])};
	}
};


class RenderObject
{
public:
	ArrayPtr<Vertex> vertices;
	ArrayPtr<Index> indices;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	RenderObject(ArrayPtr<Vertex> vertices, ArrayPtr<Index> indices);
	~RenderObject();

	void Bind() const;
	void Render() const;
	static RenderObject Triangle();
private:
	static void AddAttribute(
		GLuint index,
		GLuint type,
		GLint size,
		GLsizei stride,
		uint32_t offset);
	static void CreateBuffer(ArrayVoidPtr data, GLint type, GLuint hint,
	                         GLuint* bufferId);
};
}
