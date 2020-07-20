//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform()
    : position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1)
{

}

glm::mat4 Transform::Matrix()
{
    // TRS
    glm::mat4 result = glm::identity<glm::mat4>();
    result = glm::translate(result, position);
    result *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
    result = glm::scale(result, scale);
    return result;
}

