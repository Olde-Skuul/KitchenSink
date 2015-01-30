@echo off

:: System setup script for setting up a PC for SDKS binaries

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, check if the path is already set

where /q build.cmd
:: Found the build script, all good!
if %errorlevel% == 0 goto pathisset

if exist "%SystemDrive%\Program Files (x86)" goto path64
	setx PATH "%SDKS%\windows\bin\x86"
	set PATH="%SDKS%\windows\bin\x86";%PATH%

	goto path32
:path64
	setx PATH "%SDKS%\windows\bin\x64;%SDKS%\windows\bin\x86"
	set PATH="%SDKS%\windows\bin\x64;%SDKS%\windows\bin\x86";%PATH%
:path32

:: Exit okay!
:pathisset
exit /b

