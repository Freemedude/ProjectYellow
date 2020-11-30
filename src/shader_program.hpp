//
// @author freemedude
// @date 2020-07-18
// @brief
//
#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "shader.hpp"

class ShaderProgram
{
public:
    uint m_id = 0;
    std::vector<std::shared_ptr<Shader>> m_shaders;

    ShaderProgram(const std::vector<std::shared_ptr<Shader>> &m_shaders);
    ~ShaderProgram();

    void Use() const;

    int GetLocation(const std::string &name) const;

    void SetFloat(const std::string &name, float f);
    void SetVector3(const std::string &name, glm::vec3 vec);
    void SetVector4(const std::string &name, glm::vec4 vec);
    void SetMatrix4(const std::string &name, glm::mat4 mat);

    bool Link() const;
    bool HasSuccessfullyLinked() const;
    std::string GetInfoMessage() const;

private:
};