//
// @author freemedude
// @date 2020-07-20
// @brief 
//

#include "material.hpp"

void Material::Init(glm::vec4 color, std::shared_ptr<RasterPipeline> pipeline)
{
    m_color = color;
    m_pipeline = pipeline;
}

glm::vec4 Material::Color()
{
    return m_color;
}

std::shared_ptr<RasterPipeline> Material::Pipeline()
{
    return m_pipeline;
}
