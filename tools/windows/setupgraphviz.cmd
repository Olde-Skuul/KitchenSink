@echo off

:: System setup script for setting up a PC for using GraphViz

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: First step, set up the location of GraphViz
if not "%GRAPHVIZ%" == "" goto graphvizvarpresent
	if exist "%SystemDrive%\Program Files (x86)" goto graphviz64
	set GRAPHVIZ=%SystemDrive%\Program Files\GraphViz2.38
	goto graphviz32
:graphviz64
	set GRAPHVIZ=%SystemDrive%\Program Files (x86)\GraphViz2.38
:graphviz32
	echo Setting GRAPHVIZ=%GRAPHVIZ%
:graphvizadminokay
	setx GRAPHVIZ "%GRAPHVIZ%
:graphvizvarpresent

:: Detect if GraphViz is installed
if exist "%GRAPHVIZ%\bin\dot.exe" goto graphvizinstalled

:: Install GraphViz
:: Download the installer if needed
if exist "%~dp0graphviz-2.38.msi" goto graphvizdownloaded
echo Downloading graphviz-2.38.msi, this may take a while...
cscript /b "%~dp0downloadfile.vbs" "http://graphviz.org/pub/graphviz/stable/windows/graphviz-2.38.msi" "%~dp0graphviz-2.38.msi"
:graphvizdownloaded

:: Execute the installer
msiexec /passive /i "%~dp0graphviz-2.38.msi"
if %errorlevel% == 0 goto graphvizinstalledokay
echo Error in installing GraphViz. Manually install %~dp0graphviz-2.38.msi
exit /b 10

:: Dispose of the installer
:graphvizinstalledokay
del /q "%~dp0graphviz-2.38.msi"

:: Exit okay!
:graphvizinstalled
exit /b

