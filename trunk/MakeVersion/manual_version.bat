@echo off

ECHO #### Make Version Manually (Release)####
ECHO Please Choice Screen You Want:
ECHO 1. 128x160
ECHO 2. 176x220
ECHO 3. 240x320
ECHO 4. 320x240
SET /P INPUT=[1,2,3 or 4?]



IF %INPUT%==1 (
  SET SW=128
  SET SH=160
  SET MODEL=
) ELSE (
  IF %INPUT%==2 (
    SET SW=176
    SET SH=220
    SET MODEL=
  ) ELSE (
    IF %INPUT%==3 (
      SET SW=240
      SET SH=320
      SET MODEL=V745
    ) ELSE (
      IF %INPUT%==4 (
        SET SW=320
        SET SH=240
        SET MODEL=
      ) ELSE GOTO END
		)	
  )
)

CALL make.bat relese %SW% %SH% %MODEL%



:END
