//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "assets.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

Assets *Assets::m_instance = nullptr;

Assets::Assets()
{
    m_instance = this;
}

void Assets::Init(const char *assetDirName)
{
    m_assetsPath = GetAssetPath(assetDirName);
}

Assets &Assets::Instance()
{
    return *m_instance;
}

Image Assets::GetImage(const char *path, int channels)
{
    Assets &instance = Instance();
    File file = instance.GetFile(path);

    Image result = result.FromBytes((unsigned char *) file.Text(), (int)file.Size(), channels);
    file.Free();
    return result;
}

File Assets::GetFile(const char *path)
{

    Assets &instance = Instance();
    std::filesystem::path fullPath = instance.m_assetsPath / path;

    return File(fullPath.string().c_str());
}

std::filesystem::path Assets::GetAssetPath(const char *assetDirName)
{
    // Get current directory
    std::filesystem::path currentDir = std::filesystem::current_path();

    // Recurse upwards to find asset file
    while (currentDir.has_stem())
    {
        for (auto &dir : std::filesystem::directory_iterator(currentDir))
        {
            std::string filename = dir.path().filename().string();
            if (filename == assetDirName)
            {
                return dir.path();
            }
        }
        currentDir = currentDir.parent_path();
    }

    throw std::runtime_error("Could not find assets_root in any parent folder");
}
