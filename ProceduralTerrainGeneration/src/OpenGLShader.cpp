#include "OpenGLShader.h"

#include <glad/glad.h>
#include <iostream>



OpenGLShader::OpenGLShader(const std::string& src, Type type)
    : m_ID(0), m_Type(type)
{
    // compiling shader from source
    m_ID = glCreateShader((GLenum)m_Type);
    const char* s = src.c_str();
    glShaderSource(m_ID, 1, &s, nullptr);
    glCompileShader(m_ID);

    // checking if compilation succeeded
    GLint result;
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        // getting log message in case compilation failed
        GLint length;
        glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(m_ID, length, &length, message);
        std::string str_type;
        switch (type)
        {
        case Type::Fragment:
            str_type = "Fragment"; break;
        case Type::Vertex:
            str_type = "Vertex"; break;
        case Type::Geometry:
            str_type = "Geometry"; break;
        case Type::Compute:
            str_type = "Compute"; break;
        case Type::TesselationControl:
            str_type = "Tesselation Control"; break;
        case Type::TesselationEvaluation:
            str_type = "Tesselation Evaluation"; break;
        }
        std::cout << '[' << str_type << " Shader Compilation Error]\n" << message << "\n";
        delete[] message;
        throw;
    }
}

OpenGLShader::~OpenGLShader()
{
    // deleting shader from GPU
    Delete();
}

const char* OpenGLShader::GetShaderSource() const
{
    // retriving shader source code from GPU
    GLint length;
    glGetShaderiv(m_ID, GL_SHADER_SOURCE_LENGTH, &length);
    char* src = new char[length];
    glGetShaderSource(m_ID, length, &length, src);

    return src;
}


void OpenGLShader::Delete()
{
    glDeleteShader(m_ID);
    m_ID = 0;
}


static int GetOpenGLInt(GLenum name)
{
    int i;
    glGetIntegerv(name, &i);
    return i;
}



// shader classes
OpenGLVertexShader::OpenGLVertexShader(const std::string& src)
    : OpenGLShader(src, Type::Vertex) {}

OpenGLFragmentShader::OpenGLFragmentShader(const std::string& src)
    : OpenGLShader(src, Type::Fragment) {}

OpenGLGeometryShader::OpenGLGeometryShader(const std::string& src)
    : OpenGLShader(src, Type::Geometry) {}


// Compute Shader
OpenGLComputeShader::OpenGLComputeShader(const std::string& src)
    : OpenGLShader(src, Type::Compute) {}

int OpenGLComputeShader::GetMaxUniformBlocks()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_UNIFORM_BLOCKS);
}

int OpenGLComputeShader::GetMaxUniformComponents()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_UNIFORM_COMPONENTS);
}

int OpenGLComputeShader::GetMaxCombinedUniformComponents()
{
    return GetOpenGLInt(GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS);
}

int OpenGLComputeShader::GetMaxAtomicCounters()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_ATOMIC_COUNTERS);
}

int OpenGLComputeShader::GetMaxAtomicCounterBuffers()
{;
    return GetOpenGLInt(GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS);
}

int OpenGLComputeShader::GetMaxSharedMemorySize()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE);
}

int OpenGLComputeShader::GetMaxStorageBlock()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS);
}

int OpenGLComputeShader::GetMaxImageUniforms()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_IMAGE_UNIFORMS);
}

int OpenGLComputeShader::GetMaxTextureImageUnits()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS);
}

int OpenGLComputeShader::GetMaxWorkGroupInvocations()
{
    return GetOpenGLInt(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS);
}

glm::ivec3 OpenGLComputeShader::GetMaxWorkGroupCount()
{
    glm::ivec3 vec;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &vec.x);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &vec.y);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &vec.z);
    return vec;
}

glm::ivec3 OpenGLComputeShader::GetMaxWorkGroupSize()
{
    glm::ivec3 vec;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &vec.x);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &vec.y);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &vec.z);
    return vec;
}



// Tesselation Shaders
OpenGLTesselationShader::OpenGLTesselationShader(const std::string& src, Type type)
    : OpenGLShader(src, type) {}

int OpenGLTesselationShader::GetMaxPatchVerticies()
{
    return GetOpenGLInt(GL_MAX_PATCH_VERTICES);
}

int OpenGLTesselationShader::GetMaxGenLevel()
{
    return GetOpenGLInt(GL_MAX_TESS_GEN_LEVEL);
}

int OpenGLTesselationShader::GetMaxPatchComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_PATCH_COMPONENTS);
}



// Tesselation Control Shader
OpenGLTesselationControlShader::OpenGLTesselationControlShader(const std::string& src)
    : OpenGLTesselationShader(src, Type::TesselationControl) {}

int OpenGLTesselationControlShader::GetMaxUniformComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS);
}

int OpenGLTesselationControlShader::GetMaxUniformBlocks()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS);
}

int OpenGLTesselationControlShader::GetMaxAtomicCounters()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS);
}

int OpenGLTesselationControlShader::GetMaxAtomicCounterBuffers()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS);
}

int OpenGLTesselationControlShader::GetMaxShaderStorageBlocks()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS);
}

int OpenGLTesselationControlShader::GetMaxTextureImageUnits()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS);
}

int OpenGLTesselationControlShader::GetMaxInputComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_INPUT_COMPONENTS);
}

int OpenGLTesselationControlShader::GetMaxOutputComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS);
}

int OpenGLTesselationControlShader::GetMaxTotalOutputComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS);
}



// Tesselation Evaluation Shaders
OpenGLTesselationEvaluationShader::OpenGLTesselationEvaluationShader(const std::string& src)
    : OpenGLTesselationShader(src, Type::TesselationEvaluation) {}

int OpenGLTesselationEvaluationShader::GetMaxUniformComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS);
}

int OpenGLTesselationEvaluationShader::GetMaxUniformBlocks()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS);
}

int OpenGLTesselationEvaluationShader::GetMaxAtomicCounters()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS);
}

int OpenGLTesselationEvaluationShader::GetMaxAtomicCounterBuffers()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS);
}

int OpenGLTesselationEvaluationShader::GetMaxShaderStorageBlocks()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS);
}

int OpenGLTesselationEvaluationShader::GetMaxTextureImageUnits()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS);
}

int OpenGLTesselationEvaluationShader::GetMaxInputComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS);
}

int OpenGLTesselationEvaluationShader::GetMaxOutputComponents()
{
    return GetOpenGLInt(GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS);
}

