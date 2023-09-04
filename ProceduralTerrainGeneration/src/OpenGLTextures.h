#pragma once


class OpenGLTexture
{
public:
	enum Format
	{
		RGB8, RGBA8, ALPHA8,
		RGB32F, RGBA32F, ALPHA32F
	};

	enum DataFormat
	{
		ALPHA, RGB, RGBA
	};

	enum DataType
	{
		UBYTE, FLOAT, UINT
	};

public:
	virtual void SubData(int width, int height, void* data, DataFormat data_format = DataFormat::RGBA, DataType data_type = DataType::UBYTE, int offsetx = 0, int offsety = 0) = 0;

	unsigned int GetID() { return m_ID; };
	Format GetFormat() { return m_Format; };

protected:
	OpenGLTexture()
		: m_ID(0), m_Format(Format::RGBA8) {};

protected:
	unsigned int m_ID;
	Format m_Format;

};

class OpenGLTexture2D : public OpenGLTexture
{
public:
	OpenGLTexture2D(int width, int height, Format format);
	virtual void SubData(int width, int height, void* data, DataFormat data_format = DataFormat::RGBA, DataType data_type = DataType::UBYTE, int offsetx = 0, int offsety = 0) override;
};

