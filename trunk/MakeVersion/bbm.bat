@echo off
SETLOCAL EnableDelayedExpansion

SET BBM_H=RES_BBM.H

IF EXIST %BBM_H% (DEL /Q %BBM_H%)
echo #ifndef __BBM_H__ >> %BBM_H%
echo #define __BBM_H__ >> %BBM_H%
echo ^/^/ >> %BBM_H%
FOR /F %%i in ('dir /B *.png') DO (
  SET pngfile=%%i
  echo #define BBM_!pngfile:~0,-4!	"/!pngfile:~0,-4!.bbm" >> %BBM_H%
)
echo ^/^/ >> %BBM_H%
echo #endif >> %BBM_H%
