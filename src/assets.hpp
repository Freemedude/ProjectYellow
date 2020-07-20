//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#ifndef PROJECT_YELLOW_ASSETS_HPP
#define PROJECT_YELLOW_ASSETS_HPP

#include <string>
#include <filesystem>

#include "integers.h"

// TODO: File should be in its own file
class File
{
public:
    File(const char *path);
    ~File();

    i64 Size() const;
    char *Text();
private:
    char *m_text;
    i64 m_size;
};

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
private:
    std::filesystem::path GetAssetPath(const std::string &assetDirName);
};


#endif //PROJECT_YELLOW_ASSETS_HPP
