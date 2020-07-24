//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#ifndef PROJECT_YELLOW_IMAGE_HPP
#define PROJECT_YELLOW_IMAGE_HPP


class Image
{
public:
    int width;
    int height;
    int channels;
    int size;
    unsigned char *data;

    static Image FromBytes(unsigned char *bytes, int numBytes, int desiredChannels);

    void Free();
};


#endif //PROJECT_YELLOW_IMAGE_HPP
