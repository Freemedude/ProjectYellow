//
// @author freemedude
// @date 2020-07-20
// @brief 
//

#ifndef PROJECT_YELLOW_MATERIAL_HPP
#define PROJECT_YELLOW_MATERIAL_HPP

#include <memory>

#include <glm/glm.hpp>

#include "raster_pipeline.hpp"
#include "texture.hpp"

class Material
{
public:
    glm::vec4 m_color{};
    std::shared_ptr<RasterPipeline> m_pipeline{};
    std::shared_ptr<Texture> m_texture{};

    Material() = default;

    void Init(glm::vec4 color, std::shared_ptr<RasterPipeline> pipeline, std::shared_ptr<Texture> texture);
};


#endif //PROJECT_YELLOW_MATERIAL_HPP
