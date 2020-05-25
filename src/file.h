namespace Yellow
{
class File
{
public:
	char* text = nullptr;
	uint64_t fileSize = 0;

	File();
	File(wchar_t * filename);
	~File();

private:
    static HANDLE Win32OpenExistingFile(wchar_t *filename);
    static void Win32ReadFile(HANDLE handle, uint64_t fileSize, char* buffer);
	static uint64_t Win32GetFileSize(HANDLE handle);
};
}
