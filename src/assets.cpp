//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "assets.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>


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

