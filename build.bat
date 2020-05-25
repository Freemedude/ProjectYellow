@echo off

if not exist build mkdir build

pushd build


set argument=%1

call vcvarsall.bat x64
cl ../src/win32_yellow.cpp -Od -EHsc -Fd -Zi -nologo -I../ext -I../src user32.lib gdi32.lib Opengl32.lib

if defined argument (
	if "%argument%"=="run" (
		win32_yellow.exe
	)
	if "%argument%"=="debug" (
		remedybg open-session "../debug/yellow.rdbg"
	)
)

popd