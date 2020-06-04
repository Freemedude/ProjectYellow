bool directoryContainsFile(char *directory, char *file)
{
    HANDLE hFoundFileHandle = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAA ffd;

    hFoundFileHandle = FindFirstFileA(directory, &ffd);

    if (hFoundFileHandle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Could not find any files" << std::endl;
    }

    do
    {
        bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

        // Check if current file is
        if (!isDirectory && (strcmp(ffd.cFileName, file) == 0))
        {
            // Found the file!
            return true;
        }
    } while (FindNextFileA(hFoundFileHandle, &ffd));

    return false;
}

void replace_char(char *str, char find, char replace)
{
    char *current_pos = strchr(str, find);
    while (current_pos)
    {
        *current_pos = replace;
        current_pos = strchr(current_pos, find);
    }
}

char *GetAssetRootDirectory()
{
    // Get current directory
    char *pCurrentDirectory = new char[MAX_PATH];
    DWORD length = GetCurrentDirectoryA(MAX_PATH,
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
        char *lastSlash = strrchr(pCurrentDirectory, '/');

        lastSlash[0] = 0;
        lastSlash = strrchr(pCurrentDirectory, '/');

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

    return pCurrentDirectory;
}

File AssetManagerGetFile(char *path, bool *success)
{
    File result {};

    char pAbsoluteFilePath[MAX_PATH];

    char *pRootAssetDirectory = GetAssetRootDirectory();

    if (pAbsoluteFilePath != nullptr)
    {
        // We have located the asset directory.

        // Copy root directory to absolute file path
        strcpy(pAbsoluteFilePath, pRootAssetDirectory);

        // Trim the "*0"
        size_t length = strlen(pAbsoluteFilePath);
        pAbsoluteFilePath[length - 1] = 0;
        length -= 2;

        // Append relative file path
        strcat(pAbsoluteFilePath, "assets/");

        strcat(pAbsoluteFilePath, path);

        bool foundFile;
        result = ReadFile(pAbsoluteFilePath, &foundFile);
        *success = foundFile;
    }
    else
    {
        *success = false;
    }

    return result;
}

void CopyString(char *src, char *dst, int count)
{
}

char *GetNextLine(char *src, char *dst)
{
    // Find next newline character
    char *nextNewline = strchr(src, '\n');
    if (nextNewline != nullptr)
    {
        int charsBetween = nextNewline - src;
        // If the newline character is following a \r character
        // Remove the \r character
        if (src[charsBetween - 1] == '\r')
        {
            charsBetween--;
        }

        memcpy(dst, src, charsBetween);
        dst[charsBetween] = 0;
        return nextNewline + 1;
    }
    // We're at the end of the file
    else
    {
        char *endOfFile = strchr(src, 0);

        int charsBetween = endOfFile - src;

        memcpy(dst, src, charsBetween);
        dst[charsBetween] = 0;
        return nextNewline;
    }
}

RenderObject ImportModelOBJ(char *path)
{
    RenderObject result {};

    // Get line content
    bool foundFile = false;
    File file = AssetManagerGetFile(path, &foundFile);
    assert(foundFile);

    char *current = (char*)file.text;
    char lineBuffer[255];

    while (current != nullptr)
    {
        current = GetNextLine(current, lineBuffer);
    }
    return result;
}