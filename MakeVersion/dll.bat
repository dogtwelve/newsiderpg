@echo off
ECHO #### Generating Binary File For Emulator ####
ECHO Please Wait......

cd %PLATFORM_PATH%/%PROJ_FILENAME%

rem SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\VC\vcpackages\vcbuild.exe"
SET DLL_ERROR_REPORT_FILE=ERROR_DLL.txt
IF EXIST %DLL_ERROR_REPORT_FILE% ( DEL /Q /F %DLL_ERROR_REPORT_FILE% )
IF EXIST Debug ( RD /S /Q Debug )
IF EXIST tmp.vcproj ( DEL /F /Q tmp.vcproj )

COPY SideScroll.vcproj tmp.vcproj
kill_autobm.py tmp.vcproj

%MSDEV%  /rebuild tmp.vcproj >> %DLL_ERROR_REPORT_FILE%

if ERRORLEVEL 1 goto ERROR
goto COMPLETE

:ERROR
ECHO !!!! Error
NOTEPAD %DLL_ERROR_REPORT_FILE%
goto EXIT

:COMPLETE
ECHO !!!! Successed
IF EXIST %DLL_ERROR_REPORT_FILE% ( DEL /Q /F %DLL_ERROR_REPORT_FILE% )

:EXIT
DEL /F /Q tmp.vcproj
