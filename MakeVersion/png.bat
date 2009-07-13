@echo off

SET CONVERT_TXT=convert.txt

IF EXIST %CONVERT_TXT% ( DEL /Q %CONVERT_TXT% )
CD %DATA_OUT_PATH%

if "%1"=="EVALUATION" (
	FOR /F %%i in ('dir /B *.png') DO (
	
		if not "%%i"=="splash.png" (		
			echo %%i -565 palette(1^) >> %CONVERT_TXT%
		)
	)
) else (
	FOR /F %%i in ('dir /B *.png') DO (
	
		if not "%%i"=="splash_e.png" (		
			echo %%i -565 palette(1^) >> %CONVERT_TXT%
		)
	)
)
