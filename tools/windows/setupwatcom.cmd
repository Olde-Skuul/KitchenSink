@echo off

:: System setup script for setting up a PC for Open Watcom 1.9

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, set up the location of Watcom

if not "%WATCOM%" == "" goto watcomvarpresent
	echo Setting WATCOM="%SystemDrive%\WATCOM"
	setx WATCOM "%SystemDrive%\WATCOM"
	set WATCOM=%SystemDrive%\WATCOM
:watcomvarpresent

:: Detect if Open Watcom 1.9 is installed

if not exist "%WATCOM%\binnt\exe2bin.exe" goto installwatcom
"%WATCOM%\binnt\exe2bin.exe" -V 2>&1 | findstr /i /r "Version\ 1.9" >nul
if %errorlevel% == 0 goto watcominstalled

:: Install Open Watcom 1.9
:: Download the installer if needed
:installwatcom
if exist "%~dp0open-watcom-c-win32-1.9.exe" goto watcomdownloaded
echo Downloading Open Watcom 1.9, this may take a while...
cscript /b "%~dp0downloadfile.vbs" "http://openwatcom.mirrors.pair.com/open-watcom-c-win32-1.9.exe" "%~dp0open-watcom-c-win32-1.9.exe"
:watcomdownloaded

:: Execute the installer
"%~dp0open-watcom-c-win32-1.9.exe" -ns -i -s -dFullInstall=1
if %errorlevel% == 0 goto watcominstalledokay
echo Error in installing Watcom. Manually install %~dp0open-watcom-c-win32-1.9.exe
exit /b 10

:: Dispose of the installer
:watcominstalledokay
del /q "%~dp0open-watcom-c-win32-1.9.exe"

:: Exit okay!
:watcominstalled
exit /b

