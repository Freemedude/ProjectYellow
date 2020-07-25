//
// @author freemedude
// @date 2020-07-20
// @brief 
//

#ifndef PROJECT_YELLOW_MATERIAL_HPP
#define PROJECT_YELLOW_MATERIAL_HPP

#include <memory>

#include <glm/glm.hpp>
#include <string>

#include "raster_pipeline.hpp"
#include "texture.hpp"

class Material
{
public:
    std::string m_name;
    glm::vec4 m_color{};
    std::shared_ptr<RasterPipeline> m_pipeline{};
    std::shared_ptr<Texture> m_texture{};

    Material() = default;

    void Init(
        const std::string &name,
        glm::vec4 color,
        std::shared_ptr<RasterPipeline> pipeline,
        std::shared_ptr<Texture> texture);
};


#endif //PROJECT_YELLOW_MATERIAL_HPP
