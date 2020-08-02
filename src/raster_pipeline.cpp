//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "raster_pipeline.hpp"

#include <stdexcept>
#include <iostream>

RasterPipeline::RasterPipeline() = default;

RasterPipeline::~RasterPipeline()
{
    std::cout << "Destroyed Pipeline" << std::endl;
    glDeleteProgram(m_id);
}

void RasterPipeline::Use() const
{
    glUseProgram(m_id);
}


void RasterPipeline::Init(const char *vShaderPath, const char *fShaderPath)
{
    if (!m_vShader.Init(vShaderPath, ShaderType::Vertex))
    {
        std::string error = m_vShader.GetInfoMessage();

        std::cerr << error << std::endl;
        throw std::runtime_error(error);
    }
    if (!m_fShader.Init(fShaderPath, ShaderType::Fragment))
    {
        std::string error = m_fShader.GetInfoMessage();

        std::cerr << error << std::endl;
        throw std::runtime_error(error);
    }

    m_id = glCreateProgram();
    Link();
}

bool RasterPipeline::Link() const
{

    DetachAllShaders();

    glAttachShader(m_id, m_vShader.m_id);
    glAttachShader(m_id, m_fShader.m_id);
    glLinkProgram(m_id);

    return Valid();
}

void RasterPipeline::DetachAllShaders() const
{
    int count;
    uint attachedShaders[2];
    glGetAttachedShaders(m_id, m_maxShaders, &count, attachedShaders);

    for (int i = 0; i < count; ++i)
    {
        glDetachShader(m_id, attachedShaders[i]);
    }
}

std::string RasterPipeline::GetInfoMessage()
{
    if (Valid())
    {
        return "No messages";
    }

    int logLength;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
    std::string result;
    result.resize(logLength);
    glGetProgramInfoLog(m_id, logLength, nullptr, result.data());
    return result;
}

bool RasterPipeline::Valid() const
{
    int success = false;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    return success;
}

int RasterPipeline::GetLocation(const std::string &name) const
{
    int location = glGetUniformLocation(m_id, name.c_str());
    return location;
}

void RasterPipeline::SetMatrix4(const std::string &name, glm::mat4 mat)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniformMatrix4fv(location, 1, false, &mat[0][0]);
    }
}

void RasterPipeline::SetVector3(const std::string &name, glm::vec3 vec)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniform3fv(location, 1, &vec[0]);
    }
}

void RasterPipeline::SetFloat(const std::string &name, float f)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniform1f(location, f);
    }
}

void RasterPipeline::SetVector4(const std::string &name, glm::vec4 vec)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniform4fv(location, 1, &vec[0]);
    }
}
