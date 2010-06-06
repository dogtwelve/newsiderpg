@echo off
setlocal enabledelayedexpansion

echo ...BUILDING TEXT...

REM DIRECTORY, WHERE DATA THAT NEED TO BE PACKED, MUST BE COPIED
set DIR_TO_PACK=%1

REM DIRECTORY, WHERE DATA WHICH DON'T NEED TO BE PACKED, MUST BE COPIED
set DIR_NOT_TO_PACKED=%2

REM DIRECTORY, WHERE TO SOURCE FILES MUST BE COPIED
set DIR_SOURCE=%3

rem	--- export text from ods

	echo    encoding text in %TEXT_ENCODING%
	"%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\exportText" ExportText -d "%DIR_TO_PACK%"\ -h "%DIR_SOURCE%"\ -e %TEXT_ENCODING% TEXT.ods
	echo    encoding text in %TEXT_ENCODING%
	"%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\exportText" ExportText -d "%DIR_TO_PACK%"\ -h "%DIR_SOURCE%"\ -e %TEXT_ENCODING% TALK.ods
	echo    encoding text in %TEXT_ENCODING%
	"%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\exportText" ExportText -d "%DIR_TO_PACK%"\ -h "%DIR_SOURCE%"\ -e %TEXT_ENCODING% EVENT.ods




endlocal