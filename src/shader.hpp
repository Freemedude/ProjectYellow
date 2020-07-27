//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#ifndef PROJECT_YELLOW_SHADER_HPP
#define PROJECT_YELLOW_SHADER_HPP

#include <string>
#include <glad/glad.h>

#include "integers.h"

enum class ShaderType
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER
};

class Shader
{
public:
    const char *m_path;
    ShaderType m_type;
    uint m_id;

    Shader() = default;
    ~Shader();

    bool Init(const char *path, ShaderType type);

    bool Compile();
    std::string GetCompileError() const;
};

#endif //PROJECT_YELLOW_SHADER_HPP
