/**
 * @file: AssetManager.h
 * @author: Daniel Gaard Hansen
 * @date: 2020/04/30
 * 
 * @brief 
 * 
 * 
 */
#ifndef ASSETMANAGER_H_202004302328
#define ASSETMANAGER_H_202004302328

#include "File.h"

#define ASSET_ROOT_FILENAME L"project_yellow_asset_root.txt"

namespace Yellow
{

File GetAssetFileByRelativePath(wchar_t * path);
wchar_t *GetAssetRootDirectory();
}
#endif // ASSETMANAGER_H_202004302328