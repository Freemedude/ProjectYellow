//
// @author freemedude
// @date 2020-07-20
// @brief 
//

#include "material.hpp"

void Material::Init(
    glm::vec4 color,
    std::shared_ptr<RasterPipeline> pipeline,
    std::shared_ptr<Texture> texture)
{
    m_color = color;
    m_pipeline = pipeline;
    m_texture = texture;
}
