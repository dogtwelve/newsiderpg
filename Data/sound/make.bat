@echo off
setlocal enabledelayedexpansion

echo ...BUILDING SOUNDS...

REM DIRECTORY, WHERE DATA THAT NEED TO BE PACKED, MUST BE COPIED
set DIR_TO_PACK=%1

REM DIRECTORY, WHERE DATA WHICH DON'T NEED TO BE PACKED, MUST BE COPIED
set DIR_NOT_TO_PACKED=%2

REM DIRECTORY, WHERE TO SOURCE FILES MUST BE COPIED
set DIR_SOURCE=%3

REM copy all mid files to DIR_TO_PACK


if exist *.mid (
	copy *.mid "%DIR_TO_PACK%" > nul
)

if exist *.wav (
	copy *.mid "%DIR_TO_PACK%" > nul
)

if exist *.mmf (
	copy *.mmf "%DIR_TO_PACK%" > nul
)



endlocal




