//
// @author freemedude
// @date 2020-07-22
// @brief
//

#ifndef PROJECT_YELLOW_FILE_HPP
#define PROJECT_YELLOW_FILE_HPP

#include <string>

#include "integers.h"

class File
{
public:
    File() = default;
    File(const std::string &path);

    ~File();

    void Read(const std::string &path);

    void Write(const char *bytes);

    void Free();

    i64 Size() const;

    char *Text();

private:
    char *m_text;
    std::string m_path;
    i64 m_size;
};

#endif //PROJECT_YELLOW_FILE_HPP
