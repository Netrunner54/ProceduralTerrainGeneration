#include "OpenGLProgram.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// chacking program for linking errors
bool CheckProgramForLinkingErrors(unsigned int id)
{
	GLint result;
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	if (!result)
	{
		GLint length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(id, length, &length, message);
		std::cout << "[Program Linking Error]:\n" << message << "\n";
		delete[] message;
	}
	return !result;
}

// checking program for validation errors
bool CheckProgramForValidationErrors(unsigned int id)
{
	GLint result;
	glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		GLint length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(id, length, &length, message);
		std::cout << "[Program Validation Error]:\n" << message << "\n";
	}
	return !result;
}




// Creating from Shaders
OpenGLProgram::OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLFragmentShader& fs)
{
	LinkProgram(vs, nullptr, nullptr, nullptr, fs);
}

OpenGLProgram::OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLGeometryShader& gs, const OpenGLFragmentShader fs)
{
	LinkProgram(vs, nullptr, nullptr, &gs, fs);
}
OpenGLProgram::OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLTesselationControlShader& tcs, const OpenGLTesselationEvaluationShader& tes, const OpenGLFragmentShader fs)
{
	LinkProgram(vs, &tcs, &tes, nullptr, fs);
}
OpenGLProgram::OpenGLProgram(const OpenGLVertexShader& vs, const OpenGLTesselationControlShader& tcs, const OpenGLTesselationEvaluationShader& tes, const OpenGLGeometryShader& gs, const OpenGLFragmentShader fs)
{
	LinkProgram(vs, &tcs, &tes, &gs, fs);
}

OpenGLProgram::OpenGLProgram(const OpenGLComputeShader& cs)
{
	LinkProgram(cs);
}






// Creating from sources
OpenGLProgram::OpenGLProgram(const std::string& vs_src, const std::string& fs_src)
{
	OpenGLVertexShader vs(vs_src);
	OpenGLFragmentShader fs(fs_src);
	LinkProgram(vs, nullptr, nullptr, nullptr, fs);
}

OpenGLProgram::OpenGLProgram(const std::string& vs_src, const std::string& gs_src, const std::string& fs_src)
{
	OpenGLVertexShader vs(vs_src);
	OpenGLGeometryShader gs(gs_src);
	OpenGLFragmentShader fs(fs_src);
	LinkProgram(vs, nullptr, nullptr, &gs, fs);
}

OpenGLProgram::OpenGLProgram(const std::string& vs_src, const std::string& tcs_src, const std::string& tes_src, const std::string& fs_src)
{
	OpenGLVertexShader vs(vs_src);
	OpenGLTesselationControlShader tcs(tcs_src);
	OpenGLTesselationEvaluationShader tes(tes_src);
	OpenGLFragmentShader fs(fs_src);
	LinkProgram(vs, &tcs, &tes, nullptr, fs);
}

OpenGLProgram::OpenGLProgram(const std::string& vs_src, const std::string& tcs_src, const std::string& tes_src, const std::string& gs_src, const std::string& fs_src)
{
	OpenGLVertexShader vs(vs_src);
	OpenGLTesselationControlShader tcs(tcs_src);
	OpenGLTesselationEvaluationShader tes(tes_src);
	OpenGLGeometryShader gs(gs_src);
	OpenGLFragmentShader fs(fs_src);
	LinkProgram(vs, &tcs, &tes, &gs, fs);
}

OpenGLProgram::OpenGLProgram(const std::string& cs_src)
{
	OpenGLComputeShader cs(cs_src);
	LinkProgram(cs);
}







// Creating from Program Binary and validating
OpenGLProgram::OpenGLProgram(const ProgramBinary& prog_bin)
{
	m_ID = glCreateProgram();
	glProgramBinary(m_ID, prog_bin.format, prog_bin.binary, prog_bin.size);
	glValidateProgram(m_ID);

	if (CheckProgramForValidationErrors(m_ID))
		throw;
}

// deleting program
OpenGLProgram::~OpenGLProgram()
{
	glDeleteProgram(m_ID);
}

// retriving program binary data from GPU
ProgramBinary OpenGLProgram::GetProgramBinary() const
{
	// getting length of program binary
	GLint length;
	glGetProgramiv(m_ID, GL_PROGRAM_BINARY_LENGTH, &length);
	GLbyte* binary = new GLbyte[length];

	// getting avaliable formats
	//GLint num_of_formats;
	//glGetProgramiv(m_ID, GL_PROGRAM_BINARY_FORMATS, &num_of_formats);
	//GLenum* formats = new GLenum[num_of_formats];
	//glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, &formats);

	GLenum format;
	glGetProgramBinary(m_ID, length, &length, &format, &binary);

	return { (unsigned int)format, (unsigned int)length, binary };
}


// Uniform Blocks
unsigned int OpenGLProgram::GetUniformBlockIndex(const char* name) const
{
	return glGetUniformBlockIndex(m_ID, name);
}

void OpenGLProgram::SetUniformBlockBinding(const char* name, unsigned int binding)
{
	return glUniformBlockBinding(m_ID, GetUniformBlockIndex(name), binding);
}


/// Uniforms ///
int OpenGLProgram::GetUniformLocation(const char* name) const
{
	int location = glGetUniformLocation(m_ID, name);
	return location;
}


// Int
void OpenGLProgram::SetInt(const char* name, const int value)
{
	UploadInt(GetUniformLocation(name), value);
}

void OpenGLProgram::SetInt2(const char* name, const glm::ivec2 values)
{
	UploadInt2(GetUniformLocation(name), values);
}

void OpenGLProgram::SetInt3(const char* name, const glm::ivec3& values)
{
	UploadInt3(GetUniformLocation(name), values);
}

void OpenGLProgram::SetInt4(const char* name, const glm::ivec4& values)
{
	UploadInt4(GetUniformLocation(name), values);
}

void OpenGLProgram::SetIntArray(const char* name, int count, const int* ptr)
{
	UploadIntArray(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetInt2Array(const char* name, int count, const glm::ivec2* ptr)
{
	UploadInt2Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetInt3Array(const char* name, int count, const glm::ivec3* ptr)
{
	UploadInt3Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetInt4Array(const char* name, int count, const glm::ivec4* ptr)
{
	UploadInt4Array(GetUniformLocation(name), count, ptr);
}


// Bool
void OpenGLProgram::SetBool(const char* name, const bool value)
{
	UploadBool(GetUniformLocation(name), value);
}

void OpenGLProgram::SetBool2(const char* name, const glm::bvec2 values)
{
	UploadBool2(GetUniformLocation(name), values);
}

void OpenGLProgram::SetBool3(const char* name, const glm::bvec3& values)
{
	UploadBool3(GetUniformLocation(name), values);
}

void OpenGLProgram::SetBool4(const char* name, const glm::bvec4& values)
{
	UploadBool4(GetUniformLocation(name), values);
}


// Unsigned Int
void OpenGLProgram::SetUnsignedInt(const char* name, const unsigned int value)
{
	UploadUnsignedInt(GetUniformLocation(name), value);
}

void OpenGLProgram::SetUnsignedInt2(const char* name, const glm::uvec2 values)
{
	UploadUnsignedInt2(GetUniformLocation(name), values);
}

void OpenGLProgram::SetUnsignedInt3(const char* name, const glm::uvec3& values)
{
	UploadUnsignedInt3(GetUniformLocation(name), values);
}

void OpenGLProgram::SetUnsignedInt4(const char* name, const glm::uvec4& values)
{
	UploadUnsignedInt4(GetUniformLocation(name), values);
}

void OpenGLProgram::SetUnsignedIntArray(const char* name, int count, const unsigned int* ptr)
{
	UploadUnsignedIntArray(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetUnsignedInt2Array(const char* name, int count, const glm::uvec2* ptr)
{
	UploadUnsignedInt2Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetUnsignedInt3Array(const char* name, int count, const glm::uvec3* ptr)
{
	UploadUnsignedInt3Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetUnsignedInt4Array(const char* name, int count, const glm::uvec4* ptr)
{
	UploadUnsignedInt4Array(GetUniformLocation(name), count, ptr);
}


// Float
void OpenGLProgram::SetFloat(const char* name, const float value)
{
	UploadFloat(GetUniformLocation(name), value);
}

void OpenGLProgram::SetFloat2(const char* name, const glm::vec2 values)
{
	UploadFloat2(GetUniformLocation(name), values);
}

void OpenGLProgram::SetFloat3(const char* name, const glm::vec3& values)
{
	UploadFloat3(GetUniformLocation(name), values);
}

void OpenGLProgram::SetFloat4(const char* name, const glm::vec4& values)
{
	UploadFloat4(GetUniformLocation(name), values);
}

void OpenGLProgram::SetFloatArray(const char* name, int count, const float* ptr)
{
	UploadFloatArray(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetFloat2Array(const char* name, int count, const glm::vec2* ptr)
{
	UploadFloat2Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetFloat3Array(const char* name, int count, const glm::vec3* ptr)
{
	UploadFloat3Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetFloat4Array(const char* name, int count, const glm::vec4* ptr)
{
	UploadFloat4Array(GetUniformLocation(name), count, ptr);
}


// Double
void OpenGLProgram::SetDouble(const char* name, const double value)
{
	UploadDouble(GetUniformLocation(name), value);
}

void OpenGLProgram::SetDouble2(const char* name, const glm::dvec2 values)
{
	UploadDouble2(GetUniformLocation(name), values);
}

void OpenGLProgram::SetDouble3(const char* name, const glm::dvec3& values)
{
	UploadDouble3(GetUniformLocation(name), values);
}

void OpenGLProgram::SetDouble4(const char* name, const glm::dvec4& values)
{
	UploadDouble4(GetUniformLocation(name), values);
}

void OpenGLProgram::SetDoubleArray(const char* name, int count, const double* ptr)
{
	UploadDoubleArray(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetDouble2Array(const char* name, int count, const glm::dvec2* ptr)
{
	UploadDouble2Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetDouble3Array(const char* name, int count, const glm::dvec3* ptr)
{
	UploadDouble3Array(GetUniformLocation(name), count, ptr);
}

void OpenGLProgram::SetDouble4Array(const char* name, int count, const glm::dvec4* ptr)
{
	UploadDouble4Array(GetUniformLocation(name), count, ptr);
}


// Matrix
void OpenGLProgram::SetMat2(const char* name, const glm::mat2& mat)
{
	UploadMat2(GetUniformLocation(name), mat);
}

void OpenGLProgram::SetMat3(const char* name, const glm::mat3& mat)
{
	UploadMat3(GetUniformLocation(name), mat);
}

void OpenGLProgram::SetMat4(const char* name, const glm::mat4& mat)
{
	UploadMat4(GetUniformLocation(name), mat);
}

void OpenGLProgram::SetMat2Array(const char* name, int count, const glm::mat2* mat)
{
	UploadMat2Array(GetUniformLocation(name), count, mat);
}

void OpenGLProgram::SetMat3Array(const char* name, int count, const glm::mat3* mat)
{
	UploadMat3Array(GetUniformLocation(name), count, mat);
}

void OpenGLProgram::SetMat4Array(const char* name, int count, const glm::mat4* mat)
{
	UploadMat4Array(GetUniformLocation(name), count, mat);
}


// Double Matrices
void OpenGLProgram::SetDoubleMat2(const char* name, const glm::dmat2& mat)
{
	UploadDoubleMat2(GetUniformLocation(name), mat);
}

void OpenGLProgram::SetDoubleMat3(const char* name, const glm::dmat3& mat)
{
	UploadDoubleMat3(GetUniformLocation(name), mat);
}

void OpenGLProgram::SetDoubleMat4(const char* name, const glm::dmat4& mat)
{
	UploadDoubleMat4(GetUniformLocation(name), mat);
}

void OpenGLProgram::SetDoubleMat2Array(const char* name, int count, const glm::dmat2* mat)
{
	UploadDoubleMat2Array(GetUniformLocation(name), count, mat);
}

void OpenGLProgram::SetDoubleMat3Array(const char* name, int count, const glm::dmat3* mat)
{
	UploadDoubleMat3Array(GetUniformLocation(name), count, mat);
}

void OpenGLProgram::SetDoubleMat4Array(const char* name, int count, const glm::dmat4* mat)
{
	UploadDoubleMat4Array(GetUniformLocation(name), count, mat);
}




/// Uploads ///

// Int
void OpenGLProgram::UploadInt(int location, const int value)
{
	glUniform1i(location, value);
}

void OpenGLProgram::UploadInt2(int location, const glm::ivec2 values)
{
	glUniform2i(location, values.x, values.y);
}

void OpenGLProgram::UploadInt3(int location, const glm::ivec3& values)
{
	glUniform3i(location, values.x, values.y, values.z);
}

void OpenGLProgram::UploadInt4(int location, const glm::ivec4& values)
{
	glUniform4i(location, values.x, values.y, values.z, values.w);
}

void OpenGLProgram::UploadIntArray(int location, int count, const int* ptr)
{
	glUniform1iv(location, count, ptr);
}

void OpenGLProgram::UploadInt2Array(int location, int count, const glm::ivec2* ptr)
{
	glUniform2iv(location, count, (int*)ptr);
}

void OpenGLProgram::UploadInt3Array(int location, int count, const glm::ivec3* ptr)
{
	glUniform3iv(location, count, (int*)ptr);
}

void OpenGLProgram::UploadInt4Array(int location, int count, const glm::ivec4* ptr)
{
	glUniform4iv(location, count, (int*)ptr);
}


// Bool
void OpenGLProgram::UploadBool(int location, const bool value)
{
	UploadInt(location, value);
}

void OpenGLProgram::UploadBool2(int location, const glm::bvec2 values)
{
	UploadInt2(location, values);
}

void OpenGLProgram::UploadBool3(int location, const glm::bvec3& values)
{
	UploadInt3(location, values);
}

void OpenGLProgram::UploadBool4(int location, const glm::bvec4& values)
{
	UploadInt4(location, values);
}


// Unsigned int
void OpenGLProgram::UploadUnsignedInt(int location, const unsigned int value)
{
	glUniform1i(location, value);
}

void OpenGLProgram::UploadUnsignedInt2(int location, const glm::uvec2 values)
{
	glUniform2i(location, values.x, values.y);
}

void OpenGLProgram::UploadUnsignedInt3(int location, const glm::uvec3& values)
{
	glUniform3i(location, values.x, values.y, values.z);
}

void OpenGLProgram::UploadUnsignedInt4(int location, const glm::uvec4& values)
{
	glUniform4i(location, values.x, values.y, values.z, values.w);
}

void OpenGLProgram::UploadUnsignedIntArray(int location, int count, const unsigned int* ptr)
{
	glUniform1uiv(location, count, (const GLuint*)ptr);
}

void OpenGLProgram::UploadUnsignedInt2Array(int location, int count, const glm::uvec2* ptr)
{
	glUniform2uiv(location, count, (const GLuint*)ptr);
}

void OpenGLProgram::UploadUnsignedInt3Array(int location, int count, const glm::uvec3* ptr)
{
	glUniform3uiv(location, count, (const GLuint*)ptr);
}

void OpenGLProgram::UploadUnsignedInt4Array(int location, int count, const glm::uvec4* ptr)
{
	glUniform4uiv(location, count, (const GLuint*)ptr);
}


// Float
void OpenGLProgram::UploadFloat(int location, const float value)
{
	glUniform1f(location, value);
}

void OpenGLProgram::UploadFloat2(int location, const glm::vec2 values)
{
	glUniform2f(location, values.x, values.y);
}

void OpenGLProgram::UploadFloat3(int location, const glm::vec3& values)
{
	glUniform3f(location, values.x, values.y, values.z);
}

void OpenGLProgram::UploadFloat4(int location, const glm::vec4& values)
{
	glUniform4f(location, values.x, values.y, values.z, values.w);
}

void OpenGLProgram::UploadFloatArray(int location, int count, const float* ptr)
{
	glUniform1fv(location, count, (const GLfloat*)ptr);
}

void OpenGLProgram::UploadFloat2Array(int location, int count, const glm::vec2* ptr)
{
	glUniform2fv(location, count, (const GLfloat*)ptr);
}

void OpenGLProgram::UploadFloat3Array(int location, int count, const glm::vec3* ptr)
{
	glUniform3fv(location, count, (const GLfloat*)ptr);
}

void OpenGLProgram::UploadFloat4Array(int location, int count, const glm::vec4* ptr)
{
	glUniform4fv(location, count, (const GLfloat*)ptr);
}


// Double
void OpenGLProgram::UploadDouble(int location, const double value)
{
	glUniform1d(location, value);
}

void OpenGLProgram::UploadDouble2(int location, const glm::dvec2 values)
{
	glUniform2d(location, values.x, values.y);
}

void OpenGLProgram::UploadDouble3(int location, const glm::dvec3& values)
{
	glUniform3d(location, values.x, values.y, values.z);
}

void OpenGLProgram::UploadDouble4(int location, const glm::dvec4& values)
{
	glUniform4d(location, values.x, values.y, values.z, values.w);
}

void OpenGLProgram::UploadDoubleArray(int location, int count, const double* values)
{
	glUniform1dv(location, count, (GLdouble*)values);
}

void OpenGLProgram::UploadDouble2Array(int location, int count, const glm::dvec2* values)
{
	glUniform2dv(location, count, (GLdouble*)values);
}

void OpenGLProgram::UploadDouble3Array(int location, int count, const glm::dvec3* values)
{
	glUniform3dv(location, count, (GLdouble*)values);
}

void OpenGLProgram::UploadDouble4Array(int location, int count, const glm::dvec4* values)
{
	glUniform4dv(location, count, (GLdouble*)values);
}


// Matrices
void OpenGLProgram::UploadMat2(int location, const glm::mat2& mat)
{
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void OpenGLProgram::UploadMat3(int location, const glm::mat3& mat)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void OpenGLProgram::UploadMat4(int location, const glm::mat4& mat)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void OpenGLProgram::UploadMat2Array(int location, int count, const glm::mat2* mat)
{
	glUniformMatrix2fv(location, count, GL_FALSE, glm::value_ptr(*mat));
}

void OpenGLProgram::UploadMat3Array(int location, int count, const glm::mat3* mat)
{
	glUniformMatrix3fv(location, count, GL_FALSE, glm::value_ptr(*mat));
}

void OpenGLProgram::UploadMat4Array(int location, int count, const glm::mat4* mat)
{
	glUniformMatrix4fv(location, count, GL_FALSE, glm::value_ptr(*mat));
}


// Double Matrices
void OpenGLProgram::UploadDoubleMat2(int location, const glm::dmat2& mat)
{
	glUniformMatrix2dv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void OpenGLProgram::UploadDoubleMat3(int location, const glm::dmat3& mat)
{
	glUniformMatrix3dv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void OpenGLProgram::UploadDoubleMat4(int location, const glm::dmat4& mat)
{
	glUniformMatrix4dv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void OpenGLProgram::UploadDoubleMat2Array(int location, int count, const glm::dmat2* mat)
{
	glUniformMatrix2dv(location, count, GL_FALSE, glm::value_ptr(*mat));
}

void OpenGLProgram::UploadDoubleMat3Array(int location, int count, const glm::dmat3* mat)
{
	glUniformMatrix3dv(location, count, GL_FALSE, glm::value_ptr(*mat));
}

void OpenGLProgram::UploadDoubleMat4Array(int location, int count, const glm::dmat4* mat)
{
	glUniformMatrix4dv(location, count, GL_FALSE, glm::value_ptr(*mat));
}





// creating program, attaching shaders, linking, validating and checking for errors
// (vertex and fragment shaders are mandatory, geometry and tesselation shaders are optional)
void OpenGLProgram::LinkProgram(const OpenGLVertexShader& vs, const OpenGLTesselationControlShader* tcs, const OpenGLTesselationEvaluationShader* tes, const OpenGLGeometryShader* gs, const OpenGLFragmentShader& fs)
{
	m_ID = glCreateProgram();

	// Attaching shaders
	glAttachShader(m_ID, vs.GetID());
	glAttachShader(m_ID, fs.GetID());
	if (tcs)
		glAttachShader(m_ID, tcs->GetID());
	if (tes)
		glAttachShader(m_ID, tes->GetID());
	if (gs)
		glAttachShader(m_ID, gs->GetID());

	// Linking and checking for linking errors
	glLinkProgram(m_ID);
	if (CheckProgramForLinkingErrors(m_ID))
		throw;

	// Validating
	glValidateProgram(m_ID);
	CheckProgramForValidationErrors(m_ID);

	// Detaching shaders
	glDetachShader(m_ID, vs.GetID());
	glDetachShader(m_ID, fs.GetID());
	if (gs)
		glDetachShader(m_ID, gs->GetID());
	if (tcs)
		glDetachShader(m_ID, tcs->GetID());
	if (tes)
		glDetachShader(m_ID, tes->GetID());
}


// creating compute program, linking, validating and checking for errors
void OpenGLProgram::LinkProgram(const OpenGLComputeShader& cs)
{
	// Creating program and attaching compute shader
	m_ID = glCreateProgram();
	glAttachShader(m_ID, cs.GetID());

	// Linking and checking for linking errors
	glLinkProgram(m_ID);
	if (CheckProgramForLinkingErrors(m_ID))
		throw;
	
	// validating
	glValidateProgram(m_ID);
	CheckProgramForValidationErrors(m_ID);

	glDetachShader(m_ID, cs.GetID());
}
