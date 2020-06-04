@echo off

if not exist build mkdir build

pushd build

REM TODO: TRy out Z7

set libs=user32.lib gdi32.lib winmm.lib kernel32.lib opengl32.lib
set compiler_flags=-Od -EHsc -Zi -nologo
set linker_flags=-subsystem:windows
set includes=-I../ext -I../src

call vcvarsall.bat x64

REM TIME HERE
cl ../src/win32_yellow.cpp %compiler_flags% %includes% -link %linker_flags% %libs%
REM TO HERE
set run_mode=%1

rem If we compiled well, run
if %errorlevel%==0 (
	echo Build successful
	if "%run_mode%"=="run" (
		echo Running:
		win32_yellow.exe
	)
	if "%run_mode%"=="debug" (
		echo Debugging:
		remedybg open-session "../debug/yellow.rdbg"
	)
)

popd