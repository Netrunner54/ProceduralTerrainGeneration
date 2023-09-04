#include "OpenGLVertexArray.h"

#include <glad/glad.h>


Attribute::Attribute(Type type, unsigned int count, bool normalize)
	:_count(count), _normalize(normalize), _type(type)
{
	// all of the complex types are converted to primitive ones
	if (type >= Type::VEC2)
	{
		switch (type)
		{
		case Type::VEC2:
			_count *= 2; _type = Type::FLOAT; break;
		case Type::VEC3:
			_count *= 3; _type = Type::FLOAT; break;
		case Type::VEC4:
			_count *= 4; _type = Type::FLOAT; break;
		case Type::IVEC2:
			_count *= 2; _type = Type::INT; break;
		case Type::IVEC3:
			_count *= 3; _type = Type::INT; break;
		case Type::IVEC4:
			_count *= 4; _type = Type::INT; break;
		case Type::UVEC2:
			_count *= 2; _type = Type::UNSIGNED_INT; break;
		case Type::UVEC3:
			_count *= 3; _type = Type::UNSIGNED_INT; break;
		case Type::UVEC4:
			_count *= 4; _type = Type::UNSIGNED_INT; break;
		case Type::DVEC2:
			_count *= 2; _type = Type::DOUBLE; break;
		case Type::DVEC3:
			_count *= 3; _type = Type::DOUBLE; break;
		case Type::DVEC4:
			_count *= 4; _type = Type::DOUBLE; break;
		case Type::BVEC2:
			_count *= 2; _type = Type::BOOL; break;
		case Type::BVEC3:
			_count *= 3; _type = Type::BOOL; break;
		case Type::BVEC4:
			_count *= 4; _type = Type::BOOL; break;
		}
	}
}


void Layout::AddAttribute(const Attribute& attribute)
{
	// adding attribute to attributes list
	m_Attributes.push_back(attribute);

	// stride is extended by size of curently added attibute (OpenGL attribute not Attribute class)
	switch (attribute._type)
	{
	case Attribute::Type::FLOAT:
		m_Stride += attribute._count * sizeof(float);			break;
	case Attribute::Type::DOUBLE:
		m_Stride += attribute._count * sizeof(double);			break;
	case Attribute::Type::BYTE:
		m_Stride += attribute._count * sizeof(char);			break;
	case Attribute::Type::SHORT:
		m_Stride += attribute._count * sizeof(short);			break;
	case Attribute::Type::INT:
		m_Stride += attribute._count * sizeof(int);				break;
	case Attribute::Type::UNSIGNED_BYTE:
		m_Stride += attribute._count * sizeof(unsigned char);	break;
	case Attribute::Type::UNSIGNED_SHORT:
		m_Stride += attribute._count * sizeof(unsigned short);	break;
	case Attribute::Type::UNSIGNED_INT:
		m_Stride += attribute._count * sizeof(unsigned int);	break;
	case Attribute::Type::BOOL:
		m_Stride += attribute._count * sizeof(bool);			break;
	}
}



OpenGLVertexArray::OpenGLVertexArray()
	: m_Stride(0)
{
	glCreateVertexArrays(1, &m_ID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}

void OpenGLVertexArray::AddLayout(const Layout& layout)
{
	unsigned int i = 0;
	unsigned int ptr = 0;
	unsigned int next_ptr = 0;
	m_Stride = layout.m_Stride;
	for(const Attribute& attribute : layout.m_Attributes)
	{
		glEnableVertexArrayAttrib(m_ID, i);
		glVertexArrayAttribBinding(m_ID, i, 0);
		GLenum type;
		int count = attribute._count;
		switch (attribute._type)
		{
		case Attribute::Type::FLOAT:
			type = GL_FLOAT; next_ptr += attribute._count * sizeof(float); break;
		case Attribute::Type::DOUBLE:
			type = GL_DOUBLE; next_ptr += attribute._count * sizeof(double); break;
		case Attribute::Type::BYTE:
			type = GL_BYTE; next_ptr += attribute._count * sizeof(char); break;
		case Attribute::Type::SHORT:
			type = GL_SHORT; next_ptr += attribute._count * sizeof(short); break;
		case Attribute::Type::INT:
			type = GL_INT; next_ptr += attribute._count * sizeof(int); break;
		case Attribute::Type::UNSIGNED_BYTE:
			type = GL_UNSIGNED_BYTE; next_ptr += attribute._count * sizeof(unsigned char); break;
		case Attribute::Type::UNSIGNED_SHORT:
			type = GL_UNSIGNED_SHORT; next_ptr += attribute._count * sizeof(unsigned short); break;
		case Attribute::Type::UNSIGNED_INT:
			type = GL_UNSIGNED_INT; next_ptr += attribute._count * sizeof(unsigned int); break;
		case Attribute::Type::BOOL:
			type = GL_BOOL; next_ptr += attribute._count * sizeof(bool); break;
		default:
			type = GL_NONE;
		}
		glVertexArrayAttribFormat(m_ID, i, attribute._count, type, (attribute._normalize ? GL_TRUE : GL_FALSE), ptr);
		ptr = next_ptr;
		i++;
	}
}

void OpenGLVertexArray::AddVertexBuffer(const OpenGLVertexBuffer& vb)
{
	glVertexArrayVertexBuffer(m_ID, 0, vb.GetID(), 0, m_Stride);
}