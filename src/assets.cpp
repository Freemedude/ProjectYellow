//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "assets.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

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

Assets* Assets::m_instance = nullptr;

Assets::Assets()
{
    m_instance = this;
}

Assets &Assets::Instance()
{
    return *m_instance;
}

File Assets::GetFile(const std::string& path)
{
    std::filesystem::path fullPath = m_assetsPath / path;
    return {fullPath.string().c_str()};
}

std::filesystem::path Assets::GetAssetPath(const std::string &assetDirName)
{
    // Get current directory
    std::filesystem::path currentDir = std::filesystem::current_path();

    // Recurse upwards to find asset file
    while(currentDir.has_stem())
    {
        for(auto &dir : std::filesystem::directory_iterator(currentDir))
        {
            std::string filename = dir.path().filename().string();
            if(filename == assetDirName)
            {
                return dir.path();
            }
        }
        currentDir = currentDir.parent_path();
    }

    throw std::runtime_error("Could not find assets_root in any parent folder");
}

void Assets::Init(const std::string &assetDirName)
{
    m_assetsPath = GetAssetPath(assetDirName);
}

