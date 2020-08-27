cmake -G "Visual Studio 16 2019" .

set COMPILER="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"

if not exist %COMPILER% goto :ERRORFOUND

call %COMPILER% x86_amd64 && msbuild bomberman.sln
del "*.vcxproj*" /s /f /q
@RD /s /Q "x64"

copy Debug\bomberman.exe .
xcopy /e /v include\bin .

@RD /s /Q "Debug"
@RD /s /Q "CMakeFiles"
@RD /s /Q "bomberman.dir"
del "cmake_install*" /s /f /q
del "bomberman.sln" /s /f /q
GOTO EOF

:ERRORFOUND
echo Compiler not found. Please verify variable COMPILER.\n actual : "%COMPILER%"

:EOF
pause
