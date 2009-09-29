@echo off
y:\j2sdk1.4.2\bin\java.exe ExportText -d . -h . mapinfo.ods

if exist *.info (copy /y *.info "%DIR_TO_PACK%" > NUL)


