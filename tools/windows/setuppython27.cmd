@echo off

:: System setup script for setting up a PC for Python 2.7.9

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: Install Python
:: First step, set up the location of Python

if not "%PYTHON%" == "" goto pythonvarpresent
	echo Setting PYTHON="%SystemDrive%\Python27"
	setx PYTHON "%SystemDrive%\Python27"
	set PYTHON=%SystemDrive%\Python27
:pythonvarpresent

:: Notify Python that it should have access to Burgerlib python libraries

if not "%PYTHONPATH%" == "" goto pythonpathvarpresent
	echo Setting PYTHONPATH="%sdks%\python"
	setx PYTHONPATH "%sdks%\python"
	set PYTHONPATH=%sdks%\python
:pythonpathvarpresent

:: Detect if python 2.7.9 is installed

if not exist "%PYTHON%\python.exe" goto installpython
"%python%\python.exe" -V 2>&1 | findstr /i /r "^Python\ 2.7.9" >nul
if %errorlevel% == 0 goto pythoninstalled

:: Install python 2.7.9

:: 32 or 64 bit version of Python?
:installpython
if exist "%SystemDrive%\Program Files (x86)" goto python64
set PYTHONINSTALLER=python-2.7.9.msi
goto python32
:python64
set PYTHONINSTALLER=python-2.7.9.amd64.msi
:python32

:: Download the installer if needed
if exist "%~dp0%PYTHONINSTALLER%" goto pythondownloaded
echo Downloading Python 2.7.9, this may take a while...
cscript /nologo "%~dp0downloadfile.vbs" "http://www.python.org/ftp/python/2.7.9/%PYTHONINSTALLER%" "%~dp0%PYTHONINSTALLER%"
:pythondownloaded
:: Execute the installer
msiexec /passive /i "%~dp0%PYTHONINSTALLER%"
if %errorlevel% == 0 goto pythoninstalledokay
echo Error in installing Python. Manually install %~dp0%PYTHONINSTALLER%
exit /b 10

:: Dispose of the installer
:pythoninstalledokay
del /q "%~dp0%PYTHONINSTALLER%"

:: Exit okay!
:pythoninstalled
exit /b


