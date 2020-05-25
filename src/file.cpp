namespace Yellow
{

File::File()
{
	// Do nothing
}

File::File(wchar_t *filename)
{
	HANDLE hTextFile = Win32OpenExistingFile(filename);

	if (hTextFile == INVALID_HANDLE_VALUE)
	{

    UINT err = GetLastError();
		char errorMessage[256];
		sprintf(errorMessage, 
		         "File not found : %ws", filename);
		throw std::invalid_argument(errorMessage);
	}

	fileSize = Win32GetFileSize(hTextFile);


	// Create buffer and null terminate
	text = new char[static_cast<uint32_t>(fileSize) + 1];
	Win32ReadFile(hTextFile, fileSize, text);
    CloseHandle(hTextFile);
}

File::~File()
{
    
}

HANDLE File::Win32OpenExistingFile(wchar_t *filename)
{
	return CreateFile(
		filename,
		GENERIC_READ,
		FILE_SHARE_WRITE,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);
}

void File::Win32ReadFile(const HANDLE handle, uint64_t fileSize,
                         char* buffer)
{
	// bytesRead not used.
	DWORD bytesRead;
	ReadFile(handle, buffer, static_cast<uint32_t>(fileSize), &bytesRead, nullptr);
	buffer[fileSize] = 0;
}


uint64_t File::Win32GetFileSize(HANDLE handle)
{
	LARGE_INTEGER fileSize;
	GetFileSizeEx(handle, &fileSize);
	return fileSize.QuadPart;
}
}
