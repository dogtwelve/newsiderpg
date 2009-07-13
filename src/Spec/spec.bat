@echo off

SET SPEC_H=spec.h
IF EXIST %SPEC_H% ( DEL /F /Q %SPEC_H% )
echo #ifndef __SPEC_H__ >> %SPEC_H%
echo #define __SPEC_H__ >> %SPEC_H%
echo ^/^/ >> %SPEC_H%
FOR %%d in (W128H160 W176H220 W240H320 W320H240) DO (
  IF %%d==%1 (
    echo #define %%d 1 >> %SPEC_H%
  ) ELSE (
    echo ^/^/#define %%d 1 >> %SPEC_H%
  )
)
rem echo #define IGP_SET >> %SPEC_H%
echo #define CHEAT_ON >> %SPEC_H%
echo ^/^/ >> %SPEC_H%
IF "%2"=="PROPOSAL" (
  echo #define PROPOSAL >> %SPEC_H%
)

if "%2"=="EVALUATION" (
	echo #define EVALUATION >> %SPEC_H%
)
echo #endif >> %SPEC_H%

