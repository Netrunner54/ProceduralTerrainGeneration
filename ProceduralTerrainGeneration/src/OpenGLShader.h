#pragma once

#include <glm/glm.hpp>
#include <string>

// shader base class
class OpenGLShader
{
public:
	enum Type
	{
		// From OpenGL
		NONE = 0, Vertex = 0x8B31, Fragment = 0x8B30, Geometry = 0x8DD9, Compute = 0x91B9,
		TesselationControl = 0x8E88, TesselationEvaluation = 0x8E87	
	};

	OpenGLShader(const std::string& src, Type type);
	~OpenGLShader();

	inline unsigned int GetID() const { return m_ID; }
	const char* GetShaderSource() const;

protected:
	unsigned int m_ID;
	Type m_Type;

private:
	void Delete();	
};


// Vertex Shader
class OpenGLVertexShader : public OpenGLShader
{
public:
	OpenGLVertexShader(const std::string& src);

	// TODO: Vertex Shader Limits
};

// Fragment Shader
class OpenGLFragmentShader : public OpenGLShader
{
public:
	OpenGLFragmentShader(const std::string& src);

	// TODO: Fragment Shader Limits
};

// Geometry Shader
class OpenGLGeometryShader : public OpenGLShader
{
public:
	OpenGLGeometryShader(const std::string& src);

	// TODO: Geoemtry Shader Limits
};

// Compute Shader
class OpenGLComputeShader : public OpenGLShader
{
public:
	OpenGLComputeShader(const std::string& src);
	
	// OpenGL Implementation Compute Shader Limits
	static int GetMaxUniformBlocks();
	static int GetMaxUniformComponents();
	static int GetMaxCombinedUniformComponents();

	static int GetMaxAtomicCounters();
	static int GetMaxAtomicCounterBuffers();
	static int GetMaxSharedMemorySize();
	static int GetMaxStorageBlock();

	static int GetMaxImageUniforms();
	static int GetMaxTextureImageUnits();

	static int GetMaxWorkGroupInvocations();
	static glm::ivec3 GetMaxWorkGroupCount();
	static glm::ivec3 GetMaxWorkGroupSize();
};

// Tesselation Shader
class OpenGLTesselationShader : public OpenGLShader
{
public:
	OpenGLTesselationShader(const std::string& src, Type type);

	// OpenGL Implementation Tesselation Shaders Limits
	static int GetMaxPatchVerticies();
	static int GetMaxGenLevel();
	static int GetMaxPatchComponents();
	
};

// Tesselation Control Shader
class OpenGLTesselationControlShader : public OpenGLTesselationShader
{
public:
	OpenGLTesselationControlShader(const std::string& src);

	// OpenGL Implementation Tesselation Control Shader Limit
	static int GetMaxUniformComponents();
	static int GetMaxUniformBlocks();

	static int GetMaxAtomicCounters();
	static int GetMaxAtomicCounterBuffers();
	static int GetMaxShaderStorageBlocks();

	static int GetMaxTextureImageUnits();

	static int GetMaxInputComponents();
	static int GetMaxOutputComponents();
	static int GetMaxTotalOutputComponents();
};

// Tesselation Evaluation Shader
class OpenGLTesselationEvaluationShader : public OpenGLTesselationShader
{
public:
	OpenGLTesselationEvaluationShader(const std::string& src);

	// OpenGL Implementation Tesselation Evaluation Shader Limit
	static int GetMaxUniformComponents();
	static int GetMaxUniformBlocks();

	static int GetMaxAtomicCounters();
	static int GetMaxAtomicCounterBuffers();
	static int GetMaxShaderStorageBlocks();

	static int GetMaxTextureImageUnits();

	static int GetMaxInputComponents();
	static int GetMaxOutputComponents();
};
