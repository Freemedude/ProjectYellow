//
// @author freemedude
// @date 2020-07-19
// @brief
//
#pragma once

#include <string>
#include <glad/glad.h>

#include "integers.h"

inline void SetOpenGlLabel(uint type, uint object, std::string label)
{
    glObjectLabel(type, object, (GLsizei)label.size(), label.c_str());
}

inline std::string GetOpenGlLabel(uint type, uint object)
{
    int maxLength = -1;
    glGetIntegerv(GL_MAX_LABEL_LENGTH, &maxLength);
    std::string str;
    str.resize(maxLength);
    int actualLength = -1;
    glGetObjectLabel(type, object, maxLength, &actualLength, str.data());
    return str.substr(0, actualLength);
}