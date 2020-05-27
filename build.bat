@echo off

if not exist build mkdir build

pushd build

set libs=user32.lib gdi32.lib Opengl32.lib
set flags=-Od -EHsc -Fd -Zi -nologo
set includes=-I../ext -I../src

call vcvarsall.bat x64
cl ../src/win32_yellow.cpp %flags% %includes% %libs%

set run_mode=%1

rem If we compiled well, run
if %errorlevel%==0 (
	echo Build successful
	if "%run_mode%"=="run" (
		win32_yellow.exe
	)
	if "%run_mode%"=="debug" (
		remedybg open-session "../debug/yellow.rdbg"
	)
)

popd