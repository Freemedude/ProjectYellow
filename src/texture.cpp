//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#include "texture.hpp"

void Texture::Init(const std::string &name, std::shared_ptr<Image> image)
{
    m_image = image;
    m_buffer.Init(
        name,
        GL_TEXTURE_BUFFER,
        m_image->data,
        m_image->size,
        sizeof(m_image->data[0]));
}
