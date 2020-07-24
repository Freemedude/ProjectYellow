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
    Image result {};

    result.data = stbi_load_from_memory(bytes, size, &result.width, &result.height, &result.channels, desiredChannels);
    size = result.width * result.height * result.channels;

    return result;
}
