// FileIO.h

#include <string>
#include <wrappers/WindowsWrapper.h>


namespace Yellow
{


inline bool ReadEntireFile(const char* path, OUT char ** pText, OUT uint64_t *pFileSize)
{
	const HANDLE hTextFile = CreateFileA(
		path,
		GENERIC_READ,
		0,
		nullptr,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if(hTextFile == INVALID_HANDLE_VALUE)
	{
		printf("Failed to open file for reading: %s\n", path);
		return false;
	}

	LARGE_INTEGER fileSize;
	GetFileSizeEx(hTextFile, &fileSize);
	
	// Create buffer and all null termination
	char *buffer = new char[fileSize.QuadPart + 1];
	DWORD bytesRead;
	ReadFile(hTextFile, buffer, fileSize.QuadPart, &bytesRead, nullptr);
	buffer[fileSize.QuadPart] = 0;

	// Save to out params
	*pText = buffer;
	*pFileSize = fileSize.QuadPart;
	return true;
}
}
