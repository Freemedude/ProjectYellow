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
    GpuBuffer m_buffer{};
    std::shared_ptr<Image> m_image;

    Texture() = default;
    void Init(const std::string &name, std::shared_ptr<Image> image);
};


#endif //PROJECT_YELLOW_TEXTURE_HPP
