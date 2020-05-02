#include "File.h"

#include <stdexcept>


#include "WindowsWrapper.h"


namespace Yellow
{
File::File(wchar_t *filename)
{
	HANDLE hTextFile = Win32OpenFile(filename);

	if (hTextFile == INVALID_HANDLE_VALUE)
	{

		char errorMessage[256];
        GetLastError();
		sprintf(errorMessage, 
		         "File not found : %ws", filename);
		throw std::invalid_argument(errorMessage);
	}


	fileSize = Win32GetFileSize(hTextFile);

	// Create buffer and null terminate
	text = new char[static_cast<uint32_t>(fileSize) + 1];
	Win32ReadFile(hTextFile, fileSize, text);
}

File::~File()
{
    
}

HANDLE File::Win32OpenFile(wchar_t *filename)
{
	return CreateFile(
		filename,
		GENERIC_READ,
		0,
		nullptr,
		OPEN_ALWAYS,
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
