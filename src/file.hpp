//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#ifndef PROJECT_YELLOW_FILE_HPP
#define PROJECT_YELLOW_FILE_HPP

#include "integers.h"

class File
{
public:
    File(const char *path);
    ~File();

    i64 Size() const;
    char *Text();
private:
    char *m_text;
    i64 m_size;
};

#endif //PROJECT_YELLOW_FILE_HPP
