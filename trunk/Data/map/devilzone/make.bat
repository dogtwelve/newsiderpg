@echo off
setlocal enabledelayedexpansion

echo ...BUILDING MAPDATA...

REM DIRECTORY, WHERE DATA THAT NEED TO BE PACKED, MUST BE COPIED
set DIR_TO_PACK=%1

REM DIRECTORY, WHERE DATA WHICH DON'T NEED TO BE PACKED, MUST BE COPIED
set DIR_NOT_TO_PACKED=%2

REM DIRECTORY, WHERE TO SOURCE FILES MUST BE COPIED
set DIR_SOURCE=%3

%TOOLS_PATH%\AuroraGT\AuroraGT.exe "map.gamecmd"

	if exist *.layers (rename *.layers *.devilzone)

	if exist *.bin (copy /y *.bin "%DIR_TO_PACK%" > NUL)
	if exist *.bsprite (copy /y *.bsprite "%DIR_TO_PACK%" > NUL)
	if exist *.devilzone (copy /y *.devilzone "%DIR_TO_PACK%" > NUL)
	if exist *.cinematics (copy /y *.cinematics "%DIR_TO_PACK%" > NUL)


rem 	copy /y *.bin "%DIR_TO_PACK%" > NUL
	
rem	copy /y *.layers "%DIR_TO_PACK%" > NUL
rem	copy /y *.cinematics "%DIR_TO_PACK%" > NUL
	cd ..

:end
endlocal