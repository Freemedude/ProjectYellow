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

void Assets::Init()
{
    m_assetsPath = SearchParentForDirRecursive("assets");
}

Assets &Assets::Instance()
{
    return *m_instance;
}

Image Assets::GetImage(const std::string &path, i32 channels)
{
    Assets &instance = Instance();
    File file = instance.GetFile(path);

    Image result = result.FromBytes((unsigned char *)file.Text(), (int)file.Size(), channels);
    file.Free();
    return result;
}

File Assets::GetFile(const std::string &path)
{

    Assets &instance = Instance();
    std::filesystem::path fullPath = instance.m_assetsPath / path;

    return File(fullPath.string().c_str());
}

std::filesystem::path Assets::SearchParentForDirRecursive(const std::string &dir)
{
    // Search from CWD and upwards
    for (std::filesystem::path currentDir = std::filesystem::current_path();
         currentDir.has_stem();
         currentDir = currentDir.parent_path())
    {
        // Check all directories in currentDir.
        for (auto &check : std::filesystem::directory_iterator(currentDir))
        {
            // If their are equal to target directory.
            const std::string &filename = check.path().filename().string();
            if (filename == dir)
            {
                return check.path();
            }
        }
    }
    throw std::runtime_error("Could not find assets_root in any parent folder");
}
