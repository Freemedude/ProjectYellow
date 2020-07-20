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

class Material
{
private:
    glm::vec4 m_color {};
    std::shared_ptr<RasterPipeline> m_pipeline {};

public:
    Material() = default;

    void Init(glm::vec4 color, std::shared_ptr<RasterPipeline> pipeline);
    glm::vec4 Color();
    std::shared_ptr<RasterPipeline> Pipeline();
};


#endif //PROJECT_YELLOW_MATERIAL_HPP
