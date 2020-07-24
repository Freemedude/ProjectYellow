//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#ifndef PROJECT_YELLOW_RASTER_PIPELINE_HPP
#define PROJECT_YELLOW_RASTER_PIPELINE_HPP

#include <glm/glm.hpp>


#include "shader.hpp"


class RasterPipeline
{
private:
    Shader m_vShader{};
    Shader m_fShader{};
    uint m_id = 0;

public:
    RasterPipeline();
    ~RasterPipeline();

    void Init(const char *vShaderPath, const char* fShaderPath);
    void Use() const;
    void Reload();

    void SetMatrix4(const std::string &name, glm::mat4 mat);
    void SetFloat(const std::string &name, float f);
    void SetVector3(const std::string &name, glm::vec3 vec);
    void SetVector4(const std::string &name, glm::vec4 vec);

private:
    void Link();
    int GetLocation(const std::string &name);
};


#endif //PROJECT_YELLOW_RASTER_PIPELINE_HPP
