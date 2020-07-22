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
    m_vShader.Init(vShaderPath, ShaderType::Vertex);
    m_fShader.Init(fShaderPath, ShaderType::Fragment);

    m_id = glCreateProgram();
    Link();
}

void RasterPipeline::Link()
{
    glAttachShader(m_id, m_vShader.Id());
    glAttachShader(m_id, m_fShader.Id());
    glLinkProgram(m_id);

    int success = false;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char buffer[512];
        glGetProgramInfoLog(m_id, 512, NULL, buffer);
        std::cout << buffer << std::endl;
        throw std::runtime_error(buffer);
    }
}

void RasterPipeline::Reload()
{
    m_vShader.Compile();
    m_fShader.Compile();
    Link();
}

int RasterPipeline::GetLocation(const std::string &name)
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