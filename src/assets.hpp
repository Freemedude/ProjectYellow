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

    void Init(const char *assetDirName);

    static Assets &Instance();

    static File GetFile(const char *relativePath);

    static Image GetImage(const char *, int channels);

private:
    std::filesystem::path GetAssetPath(const char *assetDirName);
};


#endif //PROJECT_YELLOW_ASSETS_HPP
