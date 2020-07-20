//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#ifndef PROJECT_YELLOW_INPUTS_HPP
#define PROJECT_YELLOW_INPUTS_HPP

#include <glm/glm.hpp>

struct Inputs
{
    bool quit;
    bool reloadShaders;
    bool cursorLocked;
    bool invalidLastCursor;

    bool forward;
    bool back;
    bool left;
    bool right;
    bool up;
    bool down;

    glm::vec2 mousePos;
    glm::vec2 lastMousePos;
};

#endif //PROJECT_YELLOW_INPUTS_HPP
