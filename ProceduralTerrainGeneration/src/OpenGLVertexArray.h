#pragma once

#include "OpenGLBuffers.h"

#include <vector>

struct Attribute
{
public:
	enum Type
	{
		NONE = 0,
		FLOAT, DOUBLE,
		BYTE, SHORT, INT,
		UNSIGNED_BYTE, UNSIGNED_SHORT, UNSIGNED_INT,
		BOOL,
		VEC2, VEC3, VEC4,
		IVEC2, IVEC3, IVEC4,
		UVEC2, UVEC3, UVEC4,
		DVEC2, DVEC3, DVEC4,
		BVEC2, BVEC3, BVEC4
	};

public:
	Attribute() : _count(0), _normalize(false), _type(Type::NONE) {};
	Attribute(Type type, unsigned int count = 1, bool normalize = false);
	
public:
	unsigned int _count;
	bool _normalize;
	Type _type;
};



struct Layout
{
public:
	void AddAttribute(const Attribute& attribute);

public:
	std::vector<Attribute> m_Attributes;
	unsigned int m_Stride = 0;
};




class OpenGLVertexArray
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray();

	void AddLayout(const Layout& layout);
	void AddVertexBuffer(const OpenGLVertexBuffer& vb);

	unsigned int GetID() const { return m_ID; };


private:
	unsigned int m_ID, m_Stride;
};

