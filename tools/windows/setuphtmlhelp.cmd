@echo off

:: System setup script for setting up a PC for using HTML Help Workshop

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, set up the location of Help Workshop
if not "%HTMLHELP%" == "" goto htmlhelpvarpresent
	if exist "%SystemDrive%\Program Files (x86)" goto htmlhelp64
	set HTMLHELP=%SystemDrive%\Program Files\HTML Help Workshop
	goto htmlhelp32
:htmlhelp64
	set HTMLHELP=%SystemDrive%\Program Files (x86)\HTML Help Workshop
:htmlhelp32
	echo Setting HTMLHELP=%HTMLHELP%
	setx HTMLHELP "%HTMLHELP%"
:htmlhelpvarpresent

:: Detect if HTML Help Workshop is installed
if exist "%HTMLHELP%\hhc.exe" goto htmlhelpinstalled

:: Install HTML Help Workshop
:: Download the installer if needed
if exist "%~dp0htmlhelp.exe" goto htmlhelpdownloaded
echo Downloading htmlhelp.exe, this may take a while...
cscript /b "%~dp0downloadfile.vbs" "http://download.microsoft.com/download/0/A/9/0A939EF6-E31C-430F-A3DF-DFAE7960D564/htmlhelp.exe" "%~dp0htmlhelp.exe"
:htmlhelpdownloaded

:: Execute the installer
"%~dp0htmlhelp.exe" /Q:A
if %errorlevel% == 0 goto htmlinstalledokay
echo Error in installing HTML Help Workshop. Manually install %~dp0htmlhelp.exe
exit /b 10

:: Dispose of the installer
:htmlinstalledokay
del /q "%~dp0htmlhelp.exe"

:: Exit okay!
:htmlhelpinstalled
exit /b

