
del "*.vcxproj*" /s /f /q
@RD /s /Q "x64"


@RD /s /Q "Debug"
@RD /s /Q "CMakeFiles"
@RD /s /Q "bomberman.dir"
del "cmake_install*" /f /q
del "*.dll" /f /q
del "bomberman.sln" /s /f /q
pause