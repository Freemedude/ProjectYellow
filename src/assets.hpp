//
// @author freemedude
// @date 2020-07-18
// @brief Abstracts asset fetching
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

    void Init();

    static Assets &Instance();

    static File GetFile(const std::string &relativePath);

    static Image GetImage(const std::string &path, i32 channels);

private:
    std::filesystem::path SearchParentForDirRecursive(const std::string &dir);
};


#endif //PROJECT_YELLOW_ASSETS_HPP
