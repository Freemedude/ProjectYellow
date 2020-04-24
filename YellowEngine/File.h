// File.h

#pragma once
#include <string>
#include "WindowsWrapper.h"


namespace Yellow
{
class File
{
public:
	const std::string &filename;
	char* text = nullptr;
	uint64_t fileSize = 0;

	File(const std::string &filename);
	~File();

private:
	static HANDLE Win32OpenFile(const std::string& filename);
	static void Win32ReadFile(HANDLE handle, uint64_t fileSize, char* buffer);
	static uint64_t Win32GetFileSize(HANDLE handle);
};
}
