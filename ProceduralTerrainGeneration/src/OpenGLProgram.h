#pragma once

#include <glm/glm.hpp>

#include "OpenGLShader.h"

struct ProgramBinary
{
	unsigned int format;
	unsigned int size;
	void* binary;
};

class OpenGLProgram
{
public:
	// from shaders
	OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLFragmentShader& fs);
	OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLGeometryShader& gs, const OpenGLFragmentShader fs);
	OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLTesselationControlShader& tcs, const OpenGLTesselationEvaluationShader& tes, const OpenGLFragmentShader fs);
	OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLTesselationControlShader& tcs, const OpenGLTesselationEvaluationShader& tes, const OpenGLGeometryShader& gs, const OpenGLFragmentShader fs);
	OpenGLProgram(const OpenGLComputeShader& cs);

	// from source
	OpenGLProgram(const std::string& vs_src, const std::string& fs_src);
	OpenGLProgram(const std::string& vs_src, const std::string& gs_src, const std::string& fs_src);
	OpenGLProgram(const std::string& vs_src, const std::string& tcs_src, const std::string& tes_src, const std::string& fs_src);
	OpenGLProgram(const std::string& vs_src, const std::string& tcs_src, const std::string& tes_src, const std::string& gs_src, const std::string& fs_src);
	OpenGLProgram(const std::string& cs_src);

	// from binary
	OpenGLProgram(const ProgramBinary& prog_bin);

	~OpenGLProgram();

	/// Gets ///
	ProgramBinary GetProgramBinary() const;
	unsigned int GetID() const { return m_ID; };
	int GetUniformLocation(const char* name) const;




	/// Sets ///

	// Int
	void SetInt(const char* name, const int value);
	void SetInt2(const char* name, const glm::ivec2 values);
	void SetInt3(const char* name, const glm::ivec3& values);
	void SetInt4(const char* name, const glm::ivec4& values);

	void SetIntArray(const char* name, int count, const int* ptr);
	void SetInt2Array(const char* name, int count, const glm::ivec2* ptr);
	void SetInt3Array(const char* name, int count, const glm::ivec3* ptr);
	void SetInt4Array(const char* name, int count, const glm::ivec4* ptr);

	// Bool
	void SetBool(const char* name, const bool value);
	void SetBool2(const char* name, const glm::bvec2 values);
	void SetBool3(const char* name, const glm::bvec3& values);
	void SetBool4(const char* name, const glm::bvec4& values);

	// Unsigned Int
	void SetUnsignedInt(const char* name, const unsigned int value);
	void SetUnsignedInt2(const char* name, const glm::uvec2 values);
	void SetUnsignedInt3(const char* name, const glm::uvec3& values);
	void SetUnsignedInt4(const char* name, const glm::uvec4& values);

	void SetUnsignedIntArray(const char* name, int count, const unsigned int* ptr);
	void SetUnsignedInt2Array(const char* name, int count, const glm::uvec2* ptr);
	void SetUnsignedInt3Array(const char* name, int count, const glm::uvec3* ptr);
	void SetUnsignedInt4Array(const char* name, int count, const glm::uvec4* ptr);

	// Float
	void SetFloat(const char* name, const float value);
	void SetFloat2(const char* name, const glm::vec2 values);
	void SetFloat3(const char* name, const glm::vec3& values);
	void SetFloat4(const char* name, const glm::vec4& values);

	void SetFloatArray(const char* name, int count, const float* ptr);
	void SetFloat2Array(const char* name, int count, const glm::vec2* ptr);
	void SetFloat3Array(const char* name, int count, const glm::vec3* ptr);
	void SetFloat4Array(const char* name, int count, const glm::vec4* ptr);

	// Double 
	void SetDouble(const char* name, const double value);
	void SetDouble2(const char* name, const glm::dvec2 values);
	void SetDouble3(const char* name, const glm::dvec3& values);
	void SetDouble4(const char* name, const glm::dvec4& values);

	void SetDoubleArray(const char* name, int count, const double* values);
	void SetDouble2Array(const char* name, int count, const glm::dvec2* values);
	void SetDouble3Array(const char* name, int count, const glm::dvec3* values);
	void SetDouble4Array(const char* name, int count, const glm::dvec4* values);

	// Matrixes
	void SetMat2(const char* name, const glm::mat2& mat);
	void SetMat3(const char* name, const glm::mat3& mat);
	void SetMat4(const char* name, const glm::mat4& mat);

	void SetMat2Array(const char* name, int count, const glm::mat2& mat);
	void SetMat3Array(const char* name, int count, const glm::mat3& mat);
	void SetMat4Array(const char* name, int count, const glm::mat4& mat);



	/// Uploads ///

	// Int
	void UploadInt(int location, const int value);
	void UploadInt2(int location, const glm::ivec2 values);
	void UploadInt3(int location, const glm::ivec3& values);
	void UploadInt4(int location, const glm::ivec4& values);

	void UploadIntArray(int location, int count, const int* prt);
	void UploadInt2Array(int location, int count, const glm::ivec2* ptr);
	void UploadInt3Array(int location, int count, const glm::ivec3* ptr);
	void UploadInt4Array(int location, int count, const glm::ivec4* ptr);

	// Bool
	void UploadBool(int location, const bool value);
	void UploadBool2(int location, const glm::bvec2 values);
	void UploadBool3(int location, const glm::bvec3& values);
	void UploadBool4(int location, const glm::bvec4& values);

	// Unsigned Int
	void UploadUnsignedInt(int location, const unsigned int value);
	void UploadUnsignedInt2(int location, const glm::uvec2 values);
	void UploadUnsignedInt3(int location, const glm::uvec3& values);
	void UploadUnsignedInt4(int location, const glm::uvec4& values);

	void UploadUnsignedIntArray(int location, int count, const unsigned int* ptr);
	void UploadUnsignedInt2Array(int location, int count, const glm::uvec2* ptr);
	void UploadUnsignedInt3Array(int location, int count, const glm::uvec3* ptr);
	void UploadUnsignedInt4Array(int location, int count, const glm::uvec4* ptr);

	// Float
	void UploadFloat(int location, const float value);
	void UploadFloat2(int location, const glm::vec2 values);
	void UploadFloat3(int location, const glm::vec3& values);
	void UploadFloat4(int location, const glm::vec4& values);

	void UploadFloatArray(int location, int count, const float* ptr);
	void UploadFloat2Array(int location, int count, const glm::vec2* ptr);
	void UploadFloat3Array(int location, int count, const glm::vec3* ptr);
	void UploadFloat4Array(int location, int count, const glm::vec4* ptr);

	// Double 
	void UploadDouble(int location, const double value);
	void UploadDouble2(int location, const glm::dvec2 values);
	void UploadDouble3(int location, const glm::dvec3& values);
	void UploadDouble4(int location, const glm::dvec4& values);

	void UploadDoubleArray(int location, int count, const double* ptr);
	void UploadDouble2Array(int location, int count, const glm::dvec2* ptr);
	void UploadDouble3Array(int location, int count, const glm::dvec3* ptr);
	void UploadDouble4Array(int location, int count, const glm::dvec4* ptr);

	// Matrixes
	void UploadMat2(int location, const glm::mat2& mat);
	void UploadMat3(int location, const glm::mat3& mat);
	void UploadMat4(int location, const glm::mat4& mat);

	void UploadMat2Array(int location, int count, const glm::mat2& mat);
	void UploadMat3Array(int location, int count, const glm::mat3& mat);
	void UploadMat4Array(int location, int count, const glm::mat4& mat);


	inline friend bool operator==(const OpenGLProgram& lhs, const OpenGLProgram& rhs) { return lhs.m_ID == rhs.m_ID; }

private: 
	void LinkProgram(const OpenGLVertexShader& vs, const OpenGLTesselationControlShader* tcs, const OpenGLTesselationEvaluationShader* tes, const OpenGLGeometryShader* gs, const OpenGLFragmentShader& fs);
	void LinkProgram(const OpenGLComputeShader& vs);

private:
	unsigned int m_ID;
};

