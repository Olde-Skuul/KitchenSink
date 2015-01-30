@echo off

:: System setup script for setting up a PC for installing Doxygen

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, set up the location of Doxygen
if not "%DOXYGEN%" == "" goto doxygenvarpresent
	echo Setting DOXYGEN="%ProgramFiles%\doxygen"
	setx DOXYGEN "%ProgramFiles%\doxygen"
	set DOXYGEN=%ProgramFiles%\doxygen
:doxygenvarpresent

: Detect if Doxygen 1.8.7 is installed

if not exist "%DOXYGEN%\bin\doxygen.exe" goto installdoxygen
type "%DOXYGEN%\version.txt" | findstr /i /r "1.8.7" >nul
if %errorlevel% == 0 goto doxygeninstalled

:: Download the installer if needed
:installdoxygen
if exist "%~dp0doxygen-1.8.7-setup.exe" goto doxygendownloaded
echo Downloading Doxygen, this may take a while...
cscript /b "%~dp0downloadfile.vbs" "http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.7-setup.exe" "%~dp0doxygen-1.8.7-setup.exe"
:doxygendownloaded

:: Execute the installer
"%~dp0doxygen-1.8.7-setup.exe" /SP- /VERYSILENT /SUPPRESSMSGBOXES
if %errorlevel% == 0 goto doxygeninstalledokay
echo Error in installing Doxygen. Manually install %~dp0doxygen-1.8.7-setup.exe
exit /b 10

:: Dispose of the installer
:doxygeninstalledokay
del /q "%~dp0doxygen-1.8.7-setup.exe"

:: Exit okay!
:doxygeninstalled
exit /b

