//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image/stb_image.h"

Image Image::FromBytes(unsigned char *bytes, int size, int desiredChannels)
{
    Image result{};
    stbi_set_flip_vertically_on_load(true);
    result.m_data = stbi_load_from_memory(bytes, size, &result.m_width, &result.m_height, &result.m_channels, desiredChannels);
    result.m_size = result.m_width * result.m_height * result.m_channels;

    return result;
}

void Image::Free()
{
    stbi_image_free(m_data);
}
