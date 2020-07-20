//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#ifndef PROJECT_YELLOW_TRANSFORM_HPP
#define PROJECT_YELLOW_TRANSFORM_HPP

#include <glm/glm.hpp>

class Transform
{
public:
    Transform() ;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    glm::mat4 Matrix();
};


#endif //PROJECT_YELLOW_TRANSFORM_HPP
