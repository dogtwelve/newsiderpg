@echo off

SET GAME=SideScroll
set PROJ_FILENAME=SideScroll
cd..
SET PROJECT_PATH=%CD%

rem //////////////////////////
rem set useing tools path 
SET JDK_PATH=Y:\j2sdk1.4.2
rem SET BREWDIR=Y:\BREW3.1.5\sdk\src
SET WIPIDIR=Y:\WIPI SDK
SET PYTHON_HOME=Y:\Python25

rem ///////////////////////// SKT WIPIC
SET BINMAKER="%WIPIDIR%\Bin\binmaker"

rem set the text build encoding
set TEXT_ENCODING=UTF-8



SET TOOLS_PATH=%PROJECT_PATH%\Tools

rem //////////////////////////
rem set the resource build path

			rem set the directory which contain the master sources			  
			SET MASTER_DATA=%PROJECT_PATH%\Data
			rem set the directory which contains your specific sources				
			SET SPECIFIC_DATA=%PROJECT_PATH%\specific_data
			
				set DEPENDENCY=%BUILD_CONF%				

    		set WORKDIRECTORY=%PROJECT_PATH%\.version\%BUILD_CONF%
      
    		rem directory for data export
    		set DATA_PATH=%WORKDIRECTORY%\data
        rem directory where data are copied before being exported
        set DATA_PATH_RAW=%DATA_PATH%\0-data
        rem directory where data to be packed are put
        set DATA_TOPACK_PATH=%DATA_PATH%\1-dataToPack
        rem directory where data generated source files are put
        set DATA_H_PATH=%DATA_PATH%\2-dataSrc
        rem directory where data once packed are put
        set DATA_OUT_PATH=%DATA_PATH%\2-dataOut
        rem directory where the preprocessed igp config file will be put
        set IGPDATACONFIG_PATH=%DATA_PATH%\3-igpconfig
    
				set MASTER_DATA_PATH=%PROJECT_PATH%\Data


rem //////////////////////////
rem set the resource build path
		rem set the directory which contain the master sources
    SET MASTER_SRC=%PROJECT_PATH%\src
    				
				rem directory for src export
    		set SRC_PATH=%WORKDIRECTORY%\src
        rem directory where all sources are copied
        set SRC_PATH_RAW=%SRC_PATH%\0-raw
        rem directory where files once preprocessed are put
        set SRC_PATH_PREPROCESS=%SRC_PATH%\1-preprocess
        rem directory where java files once compiled are put
        set SRC_PATH_COMPILED=%SRC_PATH%\2-compiled
        rem directory where class files optimized are put
        set SRC_PATH_OPTIMIZED=%SRC_PATH%\3-optimized
        rem directory where class files are obfuscated are put
        set SRC_PATH_OBFUSCATED=%SRC_PATH%\4-obfuscated
        rem directory where class files preverified are put
        set SRC_PATH_PREVERIFIED=%SRC_PATH%\5-preverified
        rem directory where class files preverified are put
        set SRC_TOPACK_PATH=%SRC_PATH%\1-srcToPack
        rem directory for jar building
        set BUILD_PATH=%WORKDIRECTORY%\.build
        rem path were the release version will be put
        set RELEASE_PATH=%PROJ_DIR%\.release    
    
SET MAKE_PATH=%PROJECT_PATH%\MakeVersion
SET TOOLS_PATH=%PROJECT_PATH%\Tools
SET RELEASE_PATH=%PROJECT_PATH%\Release
SET PLATFORM_PATH=%PROJECT_PATH%\Project
SET SOURCECODE_PATH=%PROJECT_PATH%\src
SET DATA_PATH_H=%SOURCECODE_PATH%\game\header

SET NMAKE_EXE="C:\Program Files\Microsoft Visual Studio 8\VC\bin\NMake.exe"

SET MSDEV="C:\Program Files\Microsoft Visual Studio 8\VC\vcpackages\vcbuild.exe"
rem SET MSDEV="C:\Program Files\Microsoft Visual Studio .NET 2005\VC\vcpackages\vcbuild.exe"

SET SND_DOC_PATH=%DATA_PATH%\sound
SET MTF_TXT_PATH=%DATA_PATH%\text

SET ERROR_REPORT_FILE=%MAKE_PATH%\error.txt

SET LOCAL_LANGUAGE="KR"
