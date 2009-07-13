@echo off

SET VER_TMPFILE=ver.tmp
type "version.h"|findstr "[0-9].[0-9].[0-9]*" > %VER_TMPFILE%
FOR /F "tokens=1,2,3 delims=(.)" %%a in (%VER_TMPFILE%) do (
  SET v1=%%a
  SET v2=%%b
  SET v3=%%c
)
del /F /Q %VER_TMPFILE%
