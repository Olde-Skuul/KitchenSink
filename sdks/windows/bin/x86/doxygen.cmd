@echo off

:: Find and run doxygen as a windows batch file

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

if not "%DOXYGEN%" == "" goto doxygenpathpresent
if exist "%ProgramFiles%\Doxygen\bin\doxygen.exe" set DOXYGEN=%ProgramFiles%\Doxygen

if not "%DOXYGEN%" == "" goto doxygenpathpresent
if exist "%ProgramFiles(x86)%\Doxygen\bin\doxygen.exe" set DOXYGEN=%ProgramFiles(x86)%\Doxygen

:doxygenpathpresent
"%DOXYGEN%\bin\doxygen.exe" %*
exit /b %ERRORLEVEL%
