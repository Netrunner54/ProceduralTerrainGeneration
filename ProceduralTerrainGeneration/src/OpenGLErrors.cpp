#include "OpenGLErrors.h"
#include <glad/glad.h>
#include <iostream>
#include <cassert>



static const char* Source2String(GLenum src);
static const char* Type2String(GLenum type);
static const char* Id2String(GLenum id);
static const char* Severity2String(GLenum severity);


void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* UserParam)
{
	std::cout << "Source:    " << Source2String(source) << "\n";
	std::cout << "Type:      " << Type2String(type) << "\n";
	std::cout << "ID:        " << Id2String(id) << "\n";
	std::cout << "Severity:  " << Severity2String(severity) << "\n";
	std::cout << "Message:   " << message << "\n\n\n";
	assert(severity != GL_DEBUG_SEVERITY_HIGH);
}


void OpenGLErrors::Enable()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, nullptr);
}

void OpenGLErrors::Disable()
{
	glDisable(GL_DEBUG_OUTPUT);
}

static const char* Source2String(GLenum src)
{
	switch (src)
	{
	case GL_DEBUG_SOURCE_API:
		return "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		return "WINDOW_SYSTEM"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		return "SHADER_COMPILER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		return "THIRD_PARTY"; break;
	case GL_DEBUG_SOURCE_APPLICATION:
		return "APPLICATION"; break;
	case GL_DEBUG_SOURCE_OTHER:
		return "OTHER"; break;
	default:
		return "UNKNOWN"; break;
	}
}



static const char* Type2String(GLenum type)
{
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		return "ERROR"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		return "DEBRECATED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		return "UNDEFINED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_PORTABILITY:
		return "PORTABILITY"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		return "PERFORMANCE"; break;
	case GL_DEBUG_TYPE_OTHER:
		return "OTHER"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		return "PUSH_GROUP"; break;
	case GL_DEBUG_TYPE_POP_GROUP:
		return "POP_GROUP"; break;
	default:
		return "UNKNOWN"; break;
	}
}


static const char* Id2String(GLenum id)
{
	switch (id)
	{
	case GL_INVALID_ENUM:
		return "GL_INVALID_ENUM"; break;
	case GL_INVALID_VALUE:
		return "GL_INVALID_VALUE"; break;
	case GL_INVALID_OPERATION:
		return "GL_INVALID_OPERATION"; break;
	case GL_STACK_OVERFLOW:
		return "GL_STACK_OVERFLOW"; break;
	case GL_STACK_UNDERFLOW:
		return "GL_STACK_UNDERFLOW"; break;
	case GL_OUT_OF_MEMORY:
		return "GL_OUT_OF_MEMORY"; break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
	case GL_CONTEXT_LOST:
		return "GL_CONTEXT_LOST"; break;
		//	case GL_TABLE_TOO_LARGE:
		//		return "GL_TABLE_TOO_LARGE"; break;
	default:
		return "UNKNOWN"; break;
	}
}


static const char* Severity2String(GLenum severity)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		return "LOW"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		return "MEDIUM"; break;
	case GL_DEBUG_SEVERITY_HIGH:
		return "HIGH"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		return "NOTIFICATION"; break;
	default:
		return "UNKNOWN"; break;
	}
}