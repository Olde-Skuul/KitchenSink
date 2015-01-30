@echo off

:: Call the WiX linker "light.exe" as a windows batch file

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

if not "%WIX%" == "" goto wixvarpresent
	if "%ProgramFiles(x86)%" == "" goto wix32
	set WIX=%ProgramFiles(x86)%\WiX Toolset v3.9\
	goto wixvarpresent
:wix32
	set WIX=%ProgramFiles%\WiX Toolset v3.9\
:wixvarpresent

"%WIX%\bin\light.exe" %*
exit /b %ERRORLEVEL%
