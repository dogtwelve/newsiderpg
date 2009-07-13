
@echo off
setlocal enabledelayedexpansion

rem ---- analyse parameter
		if "%1"=="data" (
        set MAKEDATA=1
        set COMPILE=        
        set CLEAN=				

    ) else if "%1"=="release" (
        set MAKEDATA=1
        set COMPILE=1        
        set CLEAN=   
    
    ) else if "%1"=="compile" (
        set MAKEDATA=
        set COMPILE=1        
        set CLEAN=
    
    ) else if "%1"=="clean" (
        set MAKEDATA=
        set COMPILE=       
        set CLEAN=1

    ) else (
        echo make parameter [build] [SCREEN_W] [SCREEN_H] [model]
        echo   parameter[build] is one of
        echo      data    : build all data       
        echo      release : arm compile and build all data
        echo			compile : only arm compile     
        echo
        echo   parameter[model] is one of 
        echo 			example	: s330k_EN , s330k_KR
        
        goto end  
    )
		
		SET SCREEN_W=240
		SET SCREEN_H=320
		
		if not "%2"=="" (
        SET SCREEN_W=%2
    )
        
    if not "%3"=="" (
        SET SCREEN_H=%3
    )

		SET SCREEN_SOLUTION=%SCREEN_W%x%SCREEN_H%
		
		if not "%4"=="" (
        set BUILD_CONF=%4
    ) else (
    		echo make parameter [build] [SCREEN_W] [SCREEN_H] [model]
    		echo   parameter[model] is one of 
        echo   example	: S330K_EN , S330K_KR
        echo	 128x160	:		
        echo	 176x220	:		
        echo	 240x320	: S330K_EN		
        echo	 320x240	:		
        rem echo 	 S330K_EN will be inserted as parameter,
        rem echo   if there is no parameter.        
        echo	 ==no parameta==
        echo   screen_solution : %SCREEN_SOLUTION%  
        
        if not "%SCREEN_SOLUTION%%"=="240x320" (
        		
        		echo 스크린 사이즈에 따른 대표 폰 기종을 작성하세요..        		
        	
        		goto end
        )
    )



    if "%BUILD_CONF%"=="" (
			rem set default build configuration
			  set BUILD_CONF=S330K_EN
		)
    
rem ---- call user configuration file
    call set_env.bat
				
						

rem ---- Configuring Version
		echo ...Configuring Version...
		CD %MASTER_SRC%\Config
		CALL version.bat
		SET VERSION_NUM=%v1%%v2%%v3%
		echo Current Version is %v1%.%v2%.%v3%
		cd %MAKE_PATH%

		
		SET KZIP=%TOOLS_PATH%\compress\Kzip.exe
		SET ZIP_NAME=%PROJ_FILENAME%_%SCREEN_W%%SCREEN_H%_%BUILD_CONF%_V%VERSION_NUM%


rem ################################################################
rem #                                           BUILDING DATA
rem ################################################################
:makedata
		if "%MAKEDATA%"=="" (
		    goto compile
		)
:forceMakeData
    echo ###
    echo ### building data for %BUILD_CONF%
    echo ###

    cd %PROJECT_PATH%

rem ---- clear data out 
    echo ...clearing...

    if exist %DATA_PATH% (
        rd /S /Q %DATA_PATH%
    )
    md %DATA_PATH%
    md %DATA_PATH_RAW%
    md %DATA_TOPACK_PATH%
    md %DATA_H_PATH%
    md %DATA_OUT_PATH%
    md %IGPDATACONFIG_PATH%    
		
		DEL /Q %PLATFORM_PATH%\resource\*.* 
		
 
rem ---- copy master_data to data_raw
		echo ...copying master data
		xcopy /S /Y %MASTER_DATA% %DATA_PATH_RAW%\ > NUL
	
	  echo ...copying specific data
			echo ......base directory
			if exist "%SPECIFIC_DATA%" (
				xcopy /S /Y "%SPECIFIC_DATA%" %DATA_PATH_RAW%\ > NUL
			)
		echo ...depenpendy directories
		for %%i in (%DEPENDENCY%) do (
			if exist "%SPECIFIC_DATA%\%%i" (
 				xcopy /S /Y "%SPECIFIC_DATA%\%%i" %DATA_PATH_RAW%\ > NUL
			)
		)
	
		
	
rem ---- call each data make script, warning, order is important
		echo ...call each data make script, warning, order is important
    rem call data building script    
     
    
    cd %DATA_PATH_RAW%\
    call make.bat %DATA_TOPACK_PATH% %DATA_OUT_PATH% %DATA_H_PATH%
    if not %ERRORLEVEL%==0 (
        goto Error
    )
    

        	if "%5"=="_KR" (
		cd %DATA_TOPACK_PATH%
		del *_EN.LANG
		echo KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR KR
		cd %DATA_PATH_RAW%\
		
	) else (
		cd %DATA_TOPACK_PATH%
		del *_KR.LANG
		ren *_EN.LANG *_KR.LANG
		echo EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN EN
		cd %DATA_PATH_RAW%\
	)




rem ---- pack data
    Echo ...packing data...
		if not exist %DATA_PATH_RAW%\data*.ini (
        echo .....WARNING...
					echo .......file %DATA_PATH_RAW%\data-something.ini are missing...
        	echo .......no data to pack...
        goto Error
    )
		rem concat all data file into data.ini
		dir /B /ON %DATA_PATH_RAW%\data*.ini > #dir.txt
		echo //data.ini file > %DATA_PATH_RAW%\data.ini
		for /F %%i in (#dir.txt) do (
			copy %DATA_PATH_RAW%\data.ini + %%i /a > NUL
		)
		del #dir.txt
		rem pack all the data
		echo ..........pack all the data				
		rem "%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\packFile" packFile -i %DATA_TOPACK_PATH%\ -h %DATA_H_PATH%\ -d %DATA_OUT_PATH%\ -c %TOOLS_PATH%\compress\ %DATA_PATH_RAW%\data.ini
		"%JDK_PATH%\bin\java.exe" -cp "%TOOLS_PATH%\packFile" packFile -i %DATA_TOPACK_PATH%\ -d %DATA_OUT_PATH%\ -h %DATA_H_PATH%\ data.ini
    if not %ERRORLEVEL%==0 (
        echo ERROR:: error while packing data
        goto error
    )
    
    
    
rem ---- copy *.png *.mmf
		echo ...copy *.png *.mmf
		
		COPY /Y %DATA_TOPACK_PATH%\*.png %DATA_OUT_PATH%  
		COPY /Y %DATA_TOPACK_PATH%\*.mmf %DATA_OUT_PATH%  
    
    
rem ---- make png to bbm
		echo ...make png to bbm		
		
		CALL %MAKE_PATH%\png.bat
		
		MOVE convert.txt %DATA_PATH%

		CD %DATA_OUT_PATH%
		%TOOLS_PATH%\PngConvert.exe ..\convert.txt
		
		if not %ERRORLEVEL%==0 (
        echo ERROR:: error while png convert
        goto error
    )
    
		DEL %DATA_OUT_PATH%\*.png
		rem DEL convert.txt




rem ---- pack data to .bar
		echo ...pack data to .bar
		cd %DATA_OUT_PATH%
		%TOOLS_PATH%\pack.exe %DATA_OUT_PATH% res.bar
  

  
rem ---- move resource
		echo ...move resource  
		
		echo .....copy test.bar to resource
		COPY /Y %DATA_OUT_PATH%\res.bar %PLATFORM_PATH%\resource\  
	
		echo .....copy oconf.bar to resource	
		COPY /Y %DATA_PATH_RAW%\net\oconf.bar %PLATFORM_PATH%\resource\
	  
		echo .....copy font.dat to resource
		COPY /Y %DATA_PATH_RAW%\font\small_font.dat %PLATFORM_PATH%\resource\
	
		echo .....copy xrf/xaf/icon.bmp to resource
		COPY /Y %PLATFORM_PATH%\ANIMATION.xaf %PLATFORM_PATH%\resource\
		COPY /Y %PLATFORM_PATH%\icon.bmp %PLATFORM_PATH%\resource\
		COPY /Y %PLATFORM_PATH%\SideScroll.xrf %PLATFORM_PATH%\resource\

		echo .....copy Header to resourceCode  헤더파일 복사
		COPY /Y %DATA_H_PATH%\*.h %MASTER_SRC%\Data\
		
		rem echo .....copy resource to Run SideScroll		
		rem xcopy /S /Y %PLATFORM_PATH%\resource %PLATFORM_PATH%\Run\SideScroll
		
	  cd %PROJECT_PATH%
	  
	goto end 

rem ################################################################
rem #                                           ARM COMPILING
rem ################################################################
:compile
		if "%COMPILE%"=="" (
		    goto end
		)
		
rem check that data were previously build
    if not exist %DATA_PATH% (
        goto forceMakeData
    )
:forceCompile
echo ###
echo ### compiling source for %ZIP_NAME%
echo ###

		IF EXIST %ERROR_REPORT_FILE% ( DEL /Q /F %ERROR_REPORT_FILE% )

		cd %PROJECT_PATH%
rem ---- clear data out 
    echo ...clearing...
    if exist %SRC_PATH% (
        rd /S /Q %SRC_PATH%
    )
    md %SRC_PATH%		
    md %SRC_PATH_RAW%
    md %SRC_PATH_RAW%\Debug
    md %SRC_PATH_RAW%\obj
    md %SRC_PATH_RAW%\resource
    md %SRC_TOPACK_PATH%
    
    cd %SRC_TOPACK_PATH%
		FOR /D %%n in (daf device elf emu xaf) DO ( MD %%n )


		cd %MAKE_PATH%
		
		
		copy /Y %MAKE_PATH%\emu.mif %SRC_PATH_RAW%\
		copy /Y %MAKE_PATH%\dvc.mif %SRC_PATH_RAW%\
		copy /Y %MAKE_PATH%\daf.mif %SRC_PATH_RAW%\

rem ==================================
rem == Making emu
rem ==================================
		rem goto armCompile
:emuCompile		
		echo ...Making emu...
		echo .....generating dll.....
		
		CALL dll.bat
		
		xcopy /S /Y .\Debug %SRC_PATH_RAW%\Debug\ > NUL
		xcopy /S /Y %PLATFORM_PATH%\resource %SRC_PATH_RAW%\resource\ > NUL		
		
		
		echo .....binary makering(emulator).....
		cd %SRC_PATH_RAW%
		%BINMAKER% macro=emu.mif
						
		copy /Y %SRC_PATH_RAW%\Debug\%PROJ_FILENAME%.smf %SRC_TOPACK_PATH%\emu\
		copy /Y %SRC_PATH_RAW%\Debug\%PROJ_FILENAME%.dd %SRC_TOPACK_PATH%\emu\
		
rem ==================================
rem == Making phone
rem ==================================
:armCompile
		echo ...Making phone...		
		cd 	%PLATFORM_PATH%\%PROJ_FILENAME%
		
		SET ELF_ERROR_REPORT_FILE=ERROR_ELF.txt
		IF EXIST %ELF_ERROR_REPORT_FILE% ( DEL /Q /F %ELF_ERROR_REPORT_FILE% )
		
		SET path=%path%;C:\Program Files\Microsoft Visual Studio\VC98\bin;C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin
		SET Include=%Include%;C:\Program Files\Microsoft Visual Studio\VC98\Include
		SET Lib=%Lib%;C:\Program Files\Microsoft Visual Studio\VC98\Lib
		
		SET GMAKE=%TOOLS_PATH%\make.exe
		
		
		IF EXIST obj ( RD /S /Q obj )
		rem %NMAKE_EXE% -f WIPIModule.mak >> %ELF_ERROR_REPORT_FILE%
		%GMAKE% -f WIPIModule.mak >> %ELF_ERROR_REPORT_FILE%

		if ERRORLEVEL 1 (
				echo ERROR:: error make elf/arm compile
				NOTEPAD %ELF_ERROR_REPORT_FILE%
        goto error
		)		
		
		xcopy /S /Y %PLATFORM_PATH%\%PROJ_FILENAME%\obj %SRC_PATH_RAW%\obj\ > NUL			
		xcopy /S /Y %PLATFORM_PATH%\resource %SRC_PATH_RAW%\resource\ > NUL			
		
		
		echo .....binary makering(device phone)......
		cd %SRC_PATH_RAW%
		%BINMAKER% macro=dvc.mif
		
		copy /Y %SRC_PATH_RAW%\obj\%PROJ_FILENAME%.smf %SRC_TOPACK_PATH%\device\
		copy /Y %SRC_PATH_RAW%\obj\%PROJ_FILENAME%.dd %SRC_TOPACK_PATH%\device\
		
		
		echo .....binary makering(phone mod).....
		%BINMAKER% macro=daf.mif
		
		copy /Y %SRC_PATH_RAW%\obj\%PROJ_FILENAME%.daf %SRC_TOPACK_PATH%\daf\
		copy /Y %SRC_PATH_RAW%\obj\%PROJ_FILENAME%.mob %SRC_TOPACK_PATH%\daf\
		
		
		
		




		echo ...Packaging...
		
		cd %SRC_PATH%
		
		rem echo .....copying bulid_resource data
		rem xcopy /S /Y %PLATFORM_PATH%\resource %SRC_PATH%\ > NUL
		
		echo .....copying executive files
		
		echo .....copying icon.bmp/animation.xaf to \xaf
		copy /Y %SRC_PATH_RAW%\resource\icon.bmp %SRC_TOPACK_PATH%\xaf\
		copy /Y %SRC_PATH_RAW%\resource\ANIMATION.xaf %SRC_TOPACK_PATH%\xaf\
		
		

		
		cd %SRC_TOPACK_PATH%
		%KZIP% /r %ZIP_NAME% *.*
		MOVE /Y %ZIP_NAME%.zip %RELEASE_PATH%\%ZIP_NAME%.zip
		rd /s/q X:\SideScroll\Release\SideScroll_240320_V745_EN_V001
		X:\SideScroll\Release\SideScroll_240320_V745_EN_V001.zip
		
		
	goto end
		
:Error
		echo build process stopped, an error occured
		REM this is needed for the buildprocess to know there was an error  (0 == no error)
		cd %PROJECT_PATH%
		endlocal

:end
		cd %PROJECT_PATH%
		endlocal		
