//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#include "texture.hpp"

#include <string>

#include "assets.hpp"

void Texture::Init(const char *name, const char * imagePath, int channels)
{
    m_name = name;
    m_image = Assets::GetImage(imagePath, channels);

    uint format = channels == 3 ? GL_RGB : GL_RGBA;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_image.m_width, m_image.m_height, 0, format, GL_UNSIGNED_BYTE, m_image.m_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    size_t length = strlen(name);
    glObjectLabel(GL_TEXTURE, m_id, (GLsizei)length, name);
    m_image.Free();
}
