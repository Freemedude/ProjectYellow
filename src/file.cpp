//
// @author freemedude
// @date 2020-07-22
// @brief 
//

#include "file.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

File::File(const char *path)
{
    Read(path);
}

void File::Read(const char *path)
{
    m_path = path;
    std::ifstream file(path, std::ios::binary | std::ios::in);

    if (!file.good())
    {
        std::stringstream errorStream;
        errorStream << "Could not open file: " << path << "!";
        throw std::invalid_argument(errorStream.str());
    }

    file.seekg(0, std::ios::end);
    m_size = file.tellg();
    file.seekg(0, std::ios::beg);

    m_text = new char[m_size + 1];
    m_text[m_size] = 0;
    file.read(m_text, m_size);
}

File::~File()
{
    std::cout << "Destroyed file " << m_path << std::endl;
}

void File::Write(const char *bytes)
{
    std::ofstream file(m_path, std::ios::binary | std::ios::out);
    if (!file.good())
    {
        std::stringstream errorStream;
        errorStream << "Could not open file: " << m_path << "!";
        throw std::invalid_argument(errorStream.str());
    }

    file << bytes;
}

void File::Free()
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

