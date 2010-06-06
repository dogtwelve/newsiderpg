
@echo off
setlocal enabledelayedexpansion

echo ...BUILDING SPRITES...

REM DIRECTORY, WHERE DATA THAT NEED TO BE PACKED, MUST BE COPIED
set DIR_TO_PACK=%1

REM DIRECTORY, WHERE DATA WHICH DON'T NEED TO BE PACKED, MUST BE COPIED
set DIR_NOT_TO_PACKED=%2

REM DIRECTORY, WHERE TO SOURCE FILES MUST BE COPIED
set DIR_SOURCE=%3

rem	--- converting SPRITES to BSPRITES	
	"%TOOLS_PATH%\AuroraGT\AuroraGT.exe" "export.sprcmd"	
	"%PYTHON_HOME%\python.exe" "%TOOLS_PATH%\ExportAnim.py"

rem 	--- copy to output
	if exist *.bsprite (move /y *.bsprite "%DIR_TO_PACK%" > NUL)
	if exist *.java (copy /y *.java "%DIR_SOURCE%" > NUL)
rem	if exist *.h (copy /y *.h "%DIR_SOURCE%" > NUL)
	copy /y *.h "%DIR_SOURCE%" > NUL

:end
endlocal