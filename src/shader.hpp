//
// @author freemedude
// @date 2020-07-18
// @brief 
//
#pragma once

#include <string>
#include <glad/glad.h>

#include "integers.h"

enum class ShaderType
{
    UNKNOWN = 0,
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

class Shader
{
public:
    std::string m_path = nullptr;
    ShaderType m_type = ShaderType::UNKNOWN;
    uint m_id = 0;

    explicit Shader(const char* path, ShaderType type);
    ~Shader();

    bool Compile() const;
    bool Valid() const;
    std::string GetInfoMessage() const;
};