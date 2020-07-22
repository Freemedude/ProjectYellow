//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

void Camera::InitPerspective(float fov, float aspectRatio, float near, float far)
{
    m_projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
}

glm::mat4 Camera::ViewMatrix()
{
    float pitch = glm::radians(m_transform.rotation.x);
    float yaw = glm::radians(m_transform.rotation.y);

    glm::vec3 lookAt;
    lookAt.x = glm::cos(yaw) * glm::cos(pitch);
    lookAt.y = glm::sin(pitch);
    lookAt.z = glm::sin(yaw) * glm::cos(pitch);
    m_lookAt = glm::normalize(lookAt);

    return glm::lookAt(m_transform.position, m_transform.position + lookAt, {0, 1, 0});
}


glm::mat4 Camera::ProjectionMatrix()
{
    return m_projectionMatrix;
}

glm::mat4 Camera::ViewProjectionMatrix()
{
    return ProjectionMatrix() * ViewMatrix();
}

Transform &Camera::Transform()
{
    return m_transform;
}

void Camera::AddLocal(glm::vec3 v)
{
    m_transform.position += glm::normalize(glm::cross(m_lookAt, {0, 1, 0})) * v.x;
    m_transform.position += glm::vec3(0, 1, 0) * v.y;
    m_transform.position += m_lookAt * v.z;
}
