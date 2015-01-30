@echo off

:: System setup script for setting up a PC with Perforce

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, set up the location of Perforce
:: Note, this must be global due to the use of the variable
:: as a service on some machines. To set a global
:: Administrator permissions are required

if not "%PERFORCE%" == "" goto perforcevarpresent
	echo Setting PERFORCE="%ProgramFiles%\Perforce"
	:: Testing if administrator privledges are present
	net session >nul 2>&1
	if not %errorLevel% == 0 goto requiredadministratorrights
	setx PERFORCE "%ProgramFiles%\Perforce" /M
	set PERFORCE=%ProgramFiles%\Perforce
:perforcevarpresent

:: Set up a global for perforce to force it to use p4config files.

if not "%P4CONFIG%" == "" goto p4configvarpresent
	echo Setting P4CONFIG="p4config"
	:: Testing if administrator privledges are present
	net session >nul 2>&1
	if not %errorLevel% == 0 goto requiredadministratorrights
	setx P4CONFIG "p4config" /M
	set P4CONFIG=p4config
:p4configvarpresent

: Detect if Perforce 2014 is installed

if not exist "%PERFORCE%\p4.exe" goto installperforce
"%PERFORCE%\p4.exe" -V 2>&1 | findstr /i /r "\/2014.1.821990" >nul
if %errorlevel% == 0 goto perforceinstalled

:: 32 or 64 bit version of Perforce?
:installperforce
if exist "%SystemDrive%\Program Files (x86)" goto perforce64
set PERFORCEINSTALLER=p4vinst.exe
set PERFORCEHTTP=http://filehost.perforce.com/perforce/r14.1/bin.ntx86/p4vinst.exe
goto perforce32
:perforce64
set PERFORCEINSTALLER=p4vinst64.exe
set PERFORCEHTTP=http://filehost.perforce.com/perforce/r14.1/bin.ntx64/p4vinst64.exe
:perforce32

:: Download the installer if needed
if exist "%~dp0%PERFORCEINSTALLER%" goto perforcedownloaded
echo Downloading Perforce, this may take a while...
cscript /b "%~dp0downloadfile.vbs" "%PERFORCEHTTP%" "%~dp0%PERFORCEINSTALLER%"
:perforcedownloaded

:: Execute the installer
"%~dp0%PERFORCEINSTALLER%" /s /v"/qn"
if %errorlevel% == 0 goto perforceinstalledokay
echo Error in installing Perforce. Manually install %~dp0%PERFORCEINSTALLER%
exit /b 10

:: Dispose of the installer
:perforceinstalledokay
del /q "%~dp0%PERFORCEINSTALLER%"

:: Exit okay!
:perforceinstalled
exit /b

:: Epic fail in case an operation was needed that needed administrator rights
:requiredadministratorrights
echo This operation requires administrator rights to execute. Please re-run this
echo batch file from a console with administrator rights.
exit /b 10
