
@echo off
cls

Y:\j2sdk1.4.2\bin\javac *.java
if not %ERRORLEVEL%==0 (
	echo ERROR:: error while compiling
	goto error
)

java.exe ExportText -d . -h . example.ods

:error
