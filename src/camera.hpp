//
// @author freemedude
// @date 2020-07-19
// @brief
//
#pragma once

#include <glm/glm.hpp>

#include "transform.hpp"

class Camera
{
private:
    glm::mat4 m_projectionMatrix{};
    glm::vec3 m_lookAt{};

public:
    Transform m_transform{};

    Camera() = default;
    void InitPerspective(float fov, float aspectRatio, float near, float far);

    glm::mat4 ViewMatrix();
    glm::mat4 ProjectionMatrix();

    glm::vec3 &Position();
    glm::vec3 &Rotation();
    glm::vec3 &Scale();

    void AddLocal(glm::vec3 vec);
};