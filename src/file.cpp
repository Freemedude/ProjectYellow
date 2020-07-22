//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#include "file.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>


File::File(const char *path)
{
    std::ifstream file(path,  std::ios::binary |std::ios::in);

    if (!file.good())
    {
        std::stringstream errorStream;
        errorStream << "Could not open file: " << path << "!";
        throw std::invalid_argument(errorStream.str());
    }

    file.seekg (0, std::ios::end);
    m_size = file.tellg();
    file.seekg (0, std::ios::beg);

    m_text = new char[m_size + 1];
    m_text[m_size] = 0;
    file.read(m_text, m_size);
}

File::~File()
{
    delete[] m_text;
}

i64 File::Size() const
{
    return m_size;
}

char *File::Text()
{
    return m_text;
}