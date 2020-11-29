//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#ifndef PROJECT_YELLOW_RASTER_PIPELINE_HPP
#define PROJECT_YELLOW_RASTER_PIPELINE_HPP

#include <glm/glm.hpp>


#include "shader.hpp"

class ShaderProgram
{
public:
    Shader m_vShader{};
    Shader m_fShader{};
    uint m_id = 0;

    ShaderProgram();
    ~ShaderProgram();

    void Init(const char *vShaderPath, const char* fShaderPath);
    void Use() const;

    int GetLocation(const std::string &name) const;
    void SetFloat(const std::string &name, float f);
    void SetVector3(const std::string &name, glm::vec3 vec);
    void SetVector4(const std::string &name, glm::vec4 vec);
    void SetMatrix4(const std::string &name, glm::mat4 mat);

    bool Link() const;
    bool Valid() const;
    std::string GetInfoMessage() const;

    void DetachAllShaders() const;
private:
    const int m_maxShaders = 2;
};


#endif //PROJECT_YELLOW_RASTER_PIPELINE_HPP
