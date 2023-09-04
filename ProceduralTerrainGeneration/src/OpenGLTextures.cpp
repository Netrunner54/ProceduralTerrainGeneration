#include "OpenGLTextures.h"

#include <glad/glad.h>

// functions converting OpenGLTexture types to OpenGL types
static GLenum OpenGLFormat(OpenGLTexture::Format format);
static GLenum OpenGLDataFormat(OpenGLTexture::DataFormat format);
static GLenum OpenGLDataType(OpenGLTexture::DataType type);

// creating empty texture 
OpenGLTexture2D::OpenGLTexture2D(int width, int height, Format format)
{
	m_Format = format;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);

	// TODO: customizable
	glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//GLint swizzle_mask[] = { GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA };
	//glTextureParameteriv(m_ID, GL_TEXTURE_SWIZZLE_RGBA, swizzle_mask);

	GLenum f = OpenGLFormat(format);
	glTextureStorage2D(m_ID, 1, f, width, height);
}

// initializing texture
void OpenGLTexture2D::SubData(int width, int height, void* data, DataFormat data_format, DataType data_type, int offsetx, int offsety)
{
	GLenum df = OpenGLDataFormat(data_format);
	GLenum dt = OpenGLDataType(data_type);
	glTextureSubImage2D(m_ID, 0, offsetx, offsety, width, height, df, dt, data);
}

GLenum OpenGLFormat(OpenGLTexture::Format format)
{
	switch (format) {
	case OpenGLTexture::Format::RGB8:
		return GL_RGB;
	case OpenGLTexture::Format::RGBA8:
		return GL_RGBA8;
	case OpenGLTexture::Format::ALPHA8:
		return GL_R8;
	case OpenGLTexture::Format::RGB32F:
		return GL_RGB32F;
	case OpenGLTexture::Format::RGBA32F:
		return GL_RGBA32F;
	case OpenGLTexture::Format::ALPHA32F:
		return GL_R32F;
	}
}

GLenum OpenGLDataFormat(OpenGLTexture::DataFormat format)
{
	switch (format)
	{
	case OpenGLTexture::DataFormat::RGB:
		return GL_RGB;
	case OpenGLTexture::DataFormat::RGBA:
		return GL_RGBA;
	case OpenGLTexture::DataFormat::ALPHA:
		return GL_RED;
	}
}

GLenum OpenGLDataType(OpenGLTexture::DataType type)
{
	switch (type)
	{
	case OpenGLTexture::DataType::UBYTE:
		return GL_UNSIGNED_BYTE;
	case OpenGLTexture::DataType::FLOAT:
		return GL_FLOAT;
	case OpenGLTexture::DataType::UINT:
		return GL_UNSIGNED_INT;
	}
}
