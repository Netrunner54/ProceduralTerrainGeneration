#include "OpenGLBuffers.h"

#include <glad/glad.h>

OpenGLBuffer::OpenGLBuffer(int size, const void* data, bool dynamic)
{
	glCreateBuffers(1, &m_ID);
	glNamedBufferStorage(m_ID, size, data, (dynamic ? GL_DYNAMIC_STORAGE_BIT : 0x0));
}

OpenGLBuffer::~OpenGLBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void OpenGLBuffer::Data(int size, const void* data, int offset)
{
	glNamedBufferSubData(m_ID, offset, size, data);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(int size, const void* data, bool dynamic)
	: OpenGLBuffer(size, data, dynamic)
{
}

OpenGLElementBuffer::OpenGLElementBuffer(int size, const void* data, bool dynamic)
	: OpenGLBuffer(size, data, dynamic)
{
}
