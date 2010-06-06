
@echo off
setlocal enabledelayedexpansion

echo ...BUILDING ARRAY...

REM DIRECTORY, WHERE DATA THAT NEED TO BE PACKED, MUST BE COPIED
set DIR_TO_PACK=%1

REM DIRECTORY, WHERE DATA WHICH DON'T NEED TO BE PACKED, MUST BE COPIED
set DIR_NOT_TO_PACKED=%2

REM DIRECTORY, WHERE TO SOURCE FILES MUST BE COPIED
set DIR_SOURCE=%3

rem	--- binarize array files
	for %%i in (*.jpp) do (
		rem remove the -v to disable verbose mode
		"%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\binArray" BinArray -v -d "%DIR_TO_PACK%" %%i
	)

rem --- copy array files in source file for debug
	copy /y *.jpp "%DIR_SOURCE%" > NUL

:end
endlocal