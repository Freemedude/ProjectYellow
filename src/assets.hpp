//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#ifndef PROJECT_YELLOW_ASSETS_HPP
#define PROJECT_YELLOW_ASSETS_HPP

#include <string>
#include <filesystem>

#include "file.hpp"
#include "integers.h"
#include "image.hpp"

class Assets
{
private:
    static Assets *m_instance;
    std::filesystem::path m_assetsPath;

public:
    Assets();
    void Init(const std::string &assetDirName);

    static Assets& Instance();

    File GetFile(const std::string& relativePath);
    Image GetImage(const std::string& path);
private:
    std::filesystem::path GetAssetPath(const std::string &assetDirName);
};


#endif //PROJECT_YELLOW_ASSETS_HPP
