@ECHO off

ECHO #### Make Data Language####
ECHO Please Choice Language You Want:
ECHO 1. KR(한글Text)
ECHO 2. EN(영문Text)


SET /P INPUT=[1 or 2?]


IF %INPUT%==1 (
echo ##### ONLY DATA BUILD
CALL make.bat data 240 320 V745_EN _KR
) ELSE (
echo ##### ONLY DATA BUILD
CALL make.bat data 240 320 V745_EN _EN
)



pause