//
// @author freemedude
// @date 2020-07-20
// @brief 
//

#include "material.hpp"

void Material::Init(
    const std::string &name,
    glm::vec4 color,
    std::shared_ptr<ShaderProgram> program,
    std::shared_ptr<Texture> texture)
{
    m_name = name;
    m_color = color;
    m_program = program;
    m_texture = texture;
}
