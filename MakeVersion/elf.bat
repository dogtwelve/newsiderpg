@echo off
ECHO #### Generating Binary File For Phone ####
ECHO Please Wait......

SET ELF_ERROR_REPORT_FILE=ERROR_ELF.txt
IF EXIST %ELF_ERROR_REPORT_FILE% ( DEL /Q /F %ELF_ERROR_REPORT_FILE% )

SET path=%path%;C:\Program Files\Microsoft Visual Studio\VC98\bin;C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin
SET Include=%Include%;C:\Program Files\Microsoft Visual Studio\VC98\Include
SET Lib=%Lib%;C:\Program Files\Microsoft Visual Studio\VC98\Lib
SET GMAKE=..\Tools\make.exe

IF EXIST obj ( RD /S /Q obj )
%GMAKE% -f WIPIModule.mak >> %ELF_ERROR_REPORT_FILE%

if ERRORLEVEL 1 goto ERROR
goto COMPLETE

:ERROR
ECHO !!!! Error
NOTEPAD %ELF_ERROR_REPORT_FILE%
goto EXIT

:COMPLETE
ECHO !!!! Successed
IF EXIST %ELF_ERROR_REPORT_FILE% ( DEL /Q /F %ELF_ERROR_REPORT_FILE% )

:EXIT
