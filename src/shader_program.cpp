//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "shader_program.hpp"
#include "opengl_helpers.hpp"

#include <stdexcept>
#include <iostream>

ShaderProgram::ShaderProgram(const std::vector<std::shared_ptr<Shader>> &shaders)
 : m_shaders(shaders)
{
    m_id = glCreateProgram();
    Link();
}

ShaderProgram::~ShaderProgram()
{
    std::cout << "Destroyed Pipeline" << std::endl;
    glDeleteProgram(m_id);
}

void ShaderProgram::Use() const
{
    glUseProgram(m_id);
}

bool ShaderProgram::Link() const
{

    for(const auto &shader : m_shaders)
    {
        glAttachShader(m_id, shader->m_id);

    }

    glLinkProgram(m_id);
    bool valid = HasSuccessfullyLinked();
    
    for (const auto &shader : m_shaders)
    {
        glDetachShader(m_id, shader->m_id);
    }

    return valid;
}

std::string ShaderProgram::GetInfoMessage() const
{
    if (HasSuccessfullyLinked())
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

bool ShaderProgram::HasSuccessfullyLinked() const
{
    int success = false;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    return success;
}

int ShaderProgram::GetLocation(const std::string &name) const
{
    int location = glGetUniformLocation(m_id, name.c_str());
    return location;
}

void ShaderProgram::SetMatrix4(const std::string &name, glm::mat4 mat)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniformMatrix4fv(location, 1, false, &mat[0][0]);
    }
}

void ShaderProgram::SetVector3(const std::string &name, glm::vec3 vec)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniform3fv(location, 1, &vec[0]);
    }
}

void ShaderProgram::SetFloat(const std::string &name, float f)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniform1f(location, f);
    }
}

void ShaderProgram::SetVector4(const std::string &name, glm::vec4 vec)
{
    int location = GetLocation(name);
    if (location != -1)
    {
        glUniform4fv(location, 1, &vec[0]);
    }
}
