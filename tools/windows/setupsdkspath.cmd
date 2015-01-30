@echo off

:: Burgerlib projects require the existence of the environment variable SDKS
:: to point to the root of the SDKS and tools used for building.
:: This file will set SDKS to that path relative to this file,
:: assuming that this file is sitting in a folder contained in SDKS

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: Is the path already set?

if not "%SDKS%" == "" goto sdkspresent

:: Set the environment variable
	call :expand %~dp0..\..\sdks
:sdkspresent
exit /b 0

:: The only way to force a full pathname expansion is to use
:: a parameter such at %1, so call a subroutine to allow for the
:: macro expansion

:expand
setx SDKS "%~f1"
set SDKS=%~f1
exit /b