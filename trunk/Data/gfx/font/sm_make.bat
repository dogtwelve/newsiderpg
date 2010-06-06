
@echo off
setlocal enabledelayedexpansion

echo ...BUILDING FONT...

REM DIRECTORY, WHERE DATA THAT NEED TO BE PACKED, MUST BE COPIED
set DIR_TO_PACK=%1

REM DIRECTORY, WHERE DATA WHICH DON'T NEED TO BE PACKED, MUST BE COPIED
set DIR_NOT_TO_PACKED=%2

REM DIRECTORY, WHERE TO SOURCE FILES MUST BE COPIED
set DIR_SOURCE=%3

rem --- create fontTable array

	"%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\fontmap\fontmap.jar" com.gameloft.fontmap.FontMap font01.sprite fontTable.jpp
	
rem --- create fontTable array
	for %%i in (*.jpp) do (
		rem add -v to enable verbose mode
		"%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\binArray" BinArray -d "%DIR_TO_PACK%" %%i
	)
	
rem --- export font sprites
	"%TOOLS_PATH%\AuroraGT\AuroraGT_unicode.exe" "font.sprcmd"
	
rem --- copy files to output directory
	move /y *.bsprite "%DIR_TO_PACK%" > NUL
	
:end
endlocal