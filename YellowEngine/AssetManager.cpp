#include "AssetManager.h"

// System
#include <iostream>

namespace Yellow
{
bool directoryContainsFile(TCHAR *directory, TCHAR *file)
{
    HANDLE hFoundFileHandle = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAW ffd;

    hFoundFileHandle = FindFirstFile(directory, &ffd);

    if (hFoundFileHandle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Could not find any files" << std::endl;
    }

    do
    {
        bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

        // Check if current file is
        if (!isDirectory && (wcscmp(ffd.cFileName, file) == 0))
        {
            // Found the file!
            return true;
        }
    } while (FindNextFile(hFoundFileHandle, &ffd));

    return false;
}

void replace_char(wchar_t *str, wchar_t find, wchar_t replace)
{
    wchar_t *current_pos = wcschr(str, find);
    while (current_pos)
    {
        *current_pos = replace;
        current_pos = wcschr(current_pos, find);
    }
}

wchar_t *GetAssetRootDirectory()
{
    // Get current directory
    TCHAR *pCurrentDirectory = new TCHAR[MAX_PATH];
    DWORD length = GetCurrentDirectory(MAX_PATH,
                                       pCurrentDirectory);

    replace_char(pCurrentDirectory, '\\', '/');    
    if (length + 4 < MAX_PATH)
    {
        // Append "/*" and null termination
        pCurrentDirectory[length] = '/';
        pCurrentDirectory[length + 1] = '*';
        pCurrentDirectory[length + 2] = 0;
    }

    // Check for the asset root file
    while (!directoryContainsFile(pCurrentDirectory, ASSET_ROOT_FILENAME))
    {
        // Jump up one directory by chopping off last couple chars
        wchar_t *lastSlash = wcsrchr(pCurrentDirectory, '/');

        lastSlash[0] = 0;
        lastSlash = wcsrchr(pCurrentDirectory, '/');

        if (lastSlash == nullptr)
        {
            // Did not find file
            return nullptr;
        }

        // Append "/*" and null termination
        lastSlash[0] = '/';
        lastSlash[1] = '*';
        lastSlash[2] = 0;
    }

    // TODO: THIS WONT WORK, THIS IS RETURNING A DEAD POINTER
    return pCurrentDirectory;
}
    File GetAssetFileByRelativePath(wchar_t *path)
    {
        wchar_t pAbsoluteFilePath[MAX_PATH]; 
        
        wchar_t* pRootAssetDirectory = GetAssetRootDirectory();

        if(pAbsoluteFilePath != nullptr)
        {
            // We have located the asset directory.
            
            // Copy root directory to absolute file path
            wcscpy(pAbsoluteFilePath, pRootAssetDirectory);
            
            // Trim the "*0"
            size_t length = wcslen(pAbsoluteFilePath);
            pAbsoluteFilePath[length - 1] = 0;
            length -= 2;

            // Append relative file path
            wcscat(pAbsoluteFilePath, L"assets/");

            wcscat(pAbsoluteFilePath, path);
            File result(pAbsoluteFilePath);

            return result;

        }
        throw "Didn't find it";
    }

   
}
