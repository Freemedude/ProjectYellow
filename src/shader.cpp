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

void Shader::Init(const char *path, ShaderType type)
{
    m_path = path;
    m_id = glCreateShader((uint)type);
    m_type = type;

    Compile();
}

uint Shader::Id() const
{
    return m_id;
}

void Shader::Compile()
{
    // Get the text
    File source = Assets::Instance().GetFile(m_path);

    char* text = source.Text();

    glShaderSource(m_id, 1, &text, nullptr);

    // Compile it
    glCompileShader(m_id);

    int success = false;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if(!success) {
        char buffer[512];
        glGetShaderInfoLog(m_id, 512, NULL, buffer);
        std::cout << buffer << std::endl;
        throw std::runtime_error(buffer);
    }
    source.Free();
}

