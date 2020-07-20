//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#ifndef PROJECT_YELLOW_CAMERA_HPP
#define PROJECT_YELLOW_CAMERA_HPP

#include <glm/glm.hpp>

#include "transform.hpp"

class Camera
{
private:
    Transform m_transform{};
    glm::mat4 m_projectionMatrix{};
    glm::vec3 m_lookAt{};

public:
    Camera() = default;
    void InitPerspective(float fov, float aspectRatio, float near, float far);

    Transform &Transform();

    glm::mat4 ViewMatrix();
    glm::mat4 ProjectionMatrix();
    glm::mat4 ViewProjectionMatrix();

    void AddLocal(glm::vec3 vec);
};


#endif //PROJECT_YELLOW_CAMERA_HPP
