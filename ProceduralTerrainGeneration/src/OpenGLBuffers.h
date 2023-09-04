#pragma once

class OpenGLBuffer
{
public:
	OpenGLBuffer(int size, const void* data = nullptr, bool dynamic = true);
	~OpenGLBuffer();

	void Data(int size, const void* data, int offset=0);

	unsigned int GetID() const { return m_ID; }


private:
	unsigned int m_ID;
};




// Specific Buffer Objects
class OpenGLVertexBuffer : public OpenGLBuffer
{
public:
	OpenGLVertexBuffer(int size, const void* data = nullptr, bool dynamic = true);
};

class OpenGLElementBuffer : public OpenGLBuffer
{
public:
	OpenGLElementBuffer(int size, const void* data = nullptr, bool dynamic = true);
};