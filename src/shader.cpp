//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "shader.hpp"
#include "assets.hpp"

#include <iostream>

Shader::~Shader()
{

    std::cout << "Destroyed Shader" << std::endl;
    glDeleteShader(m_id);
}

bool Shader::Init(const char *path, ShaderType type)
{
    m_path = path;
    m_id = glCreateShader((uint) type);
    m_type = type;

    return Compile();
}

bool Shader::Compile()
{
    // Get the text
    File source = Assets::Instance().GetFile(m_path);

    char *text = source.Text();

    glShaderSource(m_id, 1, &text, nullptr);

    // Compile it
    glCompileShader(m_id);

    int success = false;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    source.Free();
    return success == GL_TRUE;
}

std::string Shader::GetCompileError() const
{
    int logLength;
    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
    std::string result;
    result.resize(logLength);
    glGetShaderInfoLog(m_id, logLength, nullptr, result.data());
    return result;
}