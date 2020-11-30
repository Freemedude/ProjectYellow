//
// @author freemedude
// @date 2020-07-18
// @brief
//

#include "shader.hpp"
#include "assets.hpp"

#include <iostream>

Shader::Shader(const char* path, ShaderType type)
    : m_path(path), m_type(type)
{
    m_id = glCreateShader((uint)type);

    if (!Compile())
    {
        std::string error = GetInfoMessage();

        std::cerr << error << std::endl;
        throw std::runtime_error(error);
    }
}

Shader::~Shader()
{
    std::cout << "Destroyed Shader" << std::endl;
    glDeleteShader(m_id);
}

bool Shader::Compile() const
{
    // Get the text
    File source = Assets::GetFile(m_path);

    char *text = source.Text();

    glShaderSource(m_id, 1, &text, nullptr);

    // Compile it
    glCompileShader(m_id);
    source.Free();

    bool valid = Valid();

    return valid;
}

std::string Shader::GetInfoMessage() const
{
    if (Valid())
    {
        return "No messages";
    }
    int logLength;
    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
    std::string result;
    result.resize(logLength);
    glGetShaderInfoLog(m_id, logLength, nullptr, result.data());
    return result;
}

bool Shader::Valid() const
{
    int success = false;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    return success;
}
