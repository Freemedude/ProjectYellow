// OpenGLWrapper.h

#pragma once

#include "glad/glad.h"

#include <stdexcept>
#include <assert.h>
#include <cstdio>


#if _DEBUG
// Clears all errors from the OpenGL error queue, executes contained code, then prints all errors that occured.
#define GLCall(expr) \
    GLClearErrors();\
    (expr);\
    assert(GLLogCall((#expr), __FILE__, __LINE__))

#define GLCallAssign(dest, expr) \
    GLClearErrors();\
    dest = (expr);\
    assert(GLLogCall((#expr), __FILE__, __LINE__))
#else
#define GLCall(x) (x)
#define GLCallAssign(dest, expr) \
    dest = (expr);
#endif





// Clear all errors from OpenGL Error queue
inline void GLClearErrors();

// Logs opengl errors raised during execution of 'function', with file and line information
inline bool GLLogCall(const char* function, const char* file, long line);

// Map of error code to message, use documentation per function to find actual error.
inline const char* GetErrorMessageFromCode(unsigned int code);


inline void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, long line)
{
	bool noErrors = true;
	GLenum error = glGetError();
	while (error != GL_NO_ERROR)
	{
		const char* msg = GetErrorMessageFromCode(error);
		printf("[OpenGL Error 0x%X] %s | %s | Line %d\n\t%s\n", error, file, function, line, msg);
		noErrors = false;
		error = glGetError();
	}

	return noErrors;
}

inline const char* GetErrorMessageFromCode(unsigned int code)
{
	switch (code)
	{
	case 0x500:
		return "GL_INVALID_ENUM";
	case 0x501:
		return "GL_INVALID_VALUE";
	case 0x502:
		return "GL_INVALID_OPERATION";
	case 0x503:
		return "GL_STACK_OVERFLOW";
	case 0x504:
		return "GL_STACK_UNDERFLOW";
	case 0x505:
		return "GL_OUT_OF_MEMORY";
	case 0x506:
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case 0x507:
		return "GL_CONTEXT_LOST";
	default:
		return "UNKNOWN ERROR";
	}
}