//
// @author freemedude
// @date 2020-07-22
// @brief
//
#pragma once

class Image
{
public:
    int m_width;
    int m_height;
    int m_channels;
    int m_size;
    unsigned char *m_data;

    static Image FromBytes(unsigned char *bytes, int numBytes, int desiredChannels);

    void Free();
};
