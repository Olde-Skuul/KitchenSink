@echo off

:: Call the watcom disassembler (Using the WATCOM environment variable)

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: Locate the watcom folder

if not "%WATCOM%" == "" goto watcomvarpresent
	set WATCOM=%SystemDrive%\WATCOM
:watcomvarpresent

"%watcom%\binnt\wdis.exe" %*
exit /b %ERRORLEVEL%
