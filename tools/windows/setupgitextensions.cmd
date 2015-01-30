@echo off

:: System setup script for setting up a PC for Git Extensions

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, set up the location of Git Extensions

if not "%GITEXTENSIONS%" == "" goto gitextensionsvarpresent
	if exist "%SystemDrive%\Program Files (x86)" goto gitextensions64
	set GITEXTENSIONS=%SystemDrive%\Program Files\GitExtensions
	goto gitextensions32
:gitextensions64
	set GITEXTENSIONS=%SystemDrive%\Program Files (x86)\GitExtensions
:gitextensions32
	echo Setting GITEXTENSIONS=%GITEXTENSIONS%
	setx GITEXTENSIONS "%GITEXTENSIONS%"
:gitextensionsvarpresent

:: Detect if Git Extensionsis installed
if exist "%GITEXTENSIONS%\GitExtensions.exe" goto gitextensionsinstalled

:: Install Git Extensions
:: Download the installer if needed
if exist "%~dp0GitExtensions24703SetupComplete.msi" goto gitextensionsdownloaded
echo Downloading Git Extensions 2.47.3, this may take a while...
cscript /nologo "%~dp0downloadfile.vbs" "http://iweb.dl.sourceforge.net/project/gitextensions/Git Extensions/Version 2.47.03/GitExtensions24703SetupComplete.msi" "%~dp0GitExtensions24703SetupComplete.msi"
:gitextensionsdownloaded

:: Execute the installer
msiexec /passive /i "%~dp0GitExtensions24703SetupComplete.msi"
if %errorlevel% == 0 goto gitextensionsinstalledokay
echo Error in installing Git Extensions. Manually install %~dp0GitExtensions24703SetupComplete.msi
exit /b 10

:: Dispose of the installer
:gitextensionsinstalledokay
del /q "%~dp0GitExtensions24703SetupComplete.msi"

:: Exit okay!
:gitextensionsinstalled
exit /b
