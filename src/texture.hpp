//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#ifndef PROJECT_YELLOW_TEXTURE_HPP
#define PROJECT_YELLOW_TEXTURE_HPP

#include <memory>

#include "gpu_buffer.hpp"
#include "image.hpp"

class Texture
{
public:
    Image m_image;
    std::string m_name;
    uint m_id = 0;

    Texture() = default;

    void Init(const char *name, const char *imagePath, int channels);
};


#endif //PROJECT_YELLOW_TEXTURE_HPP
