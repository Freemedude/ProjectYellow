/**
 * @file: AssetManager.h
 * @author: Daniel Gaard Hansen
 * @date: 2020/04/30
 * 
 * @brief Contains functions for asset management
 * 
 * 
 */
#ifndef ASSETMANAGER_H_202004302328
#define ASSETMANAGER_H_202004302328

#include "File.h"
#include "Rendering.h"

#define ASSET_ROOT_FILENAME L"project_yellow_asset_root.txt"

namespace Yellow
{
wchar_t *GetAssetRootDirectory();
RenderObject ImportModelOBJ(wchar_t *path);

File GetAssetFileByRelativePath(wchar_t * path);
}
#endif // ASSETMANAGER_H_202004302328