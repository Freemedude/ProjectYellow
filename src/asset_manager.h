/**
 * @file: AssetManager.h
 * @author: Daniel Gaard Hansen
 * @date: 2020/04/30
 *
 * @brief Contains functions for asset management
 *
 *
 */
#define ASSET_ROOT_FILENAME "project_yellow_asset_root.txt"

char *GetAssetRootDirectory();
RenderObject ImportModelOBJ(char *path);

File AssetManagerGetFile(char * path, bool *success);