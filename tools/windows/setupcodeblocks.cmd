@echo off

:: System setup script for setting up a PC for CodeBlocks

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, set up the location of CodeBlocks

if not "%CODEBLOCKS%" == "" goto codeblocksvarpresent
	if exist "%SystemDrive%\Program Files (x86)" goto codeblocks64
	set CODEBLOCKS=%SystemDrive%\Program Files\CodeBlocks
	goto codeblocks32
:codeblocks64
	set CODEBLOCKS=%SystemDrive%\Program Files (x86)\CodeBlocks
:codeblocks32
	echo Setting CODEBLOCKS=%CODEBLOCKS%
	setx CODEBLOCKS "%CODEBLOCKS%"
:codeblocksvarpresent

:: Detect if CodeBlocks is installed
if exist "%CODEBLOCKS%\codeblocks.exe" goto codeblocksinstalled

:: Install Codeblocks
:: Download the installer if needed
if exist "%~dp0codeblocks-13.12-setup.exe" goto codeblocksdownloaded
echo Downloading codeblocks-13.12, this may take a while...
cscript /b "%~dp0downloadfile.vbs" "http://iweb.dl.sourceforge.net/project/codeblocks/Binaries/13.12/Windows/codeblocks-13.12-setup.exe" "%~dp0codeblocks-13.12-setup.exe"
:codeblocksdownloaded

:: Execute the installer
"%~dp0codeblocks-13.12-setup.exe" /S
if %errorlevel% == 0 goto codeblocksinstalledokay
:: For some odd reason, the CodeBlocks installer returns 2 on a good install
if %errorlevel% == 2 goto codeblocksinstalledokay
echo Error in installing Codeblocks. Manually install %~dp0codeblocks-13.12-setup.exe
exit /b 10

:: Dispose of the installer
:codeblocksinstalledokay
del /q "%~dp0codeblocks-13.12-setup.exe"

:: Exit okay!
:codeblocksinstalled
exit /b
