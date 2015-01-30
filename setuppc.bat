@echo off

:: System setup script for setting up a PC for developing with Burgerlib

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: Set up the SDKS environment variable

call "%~dp0tools\windows\setupsdkspath.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Enable Visual studio to pull microsoft symbols from the symbol server
:: Invoke from a standalone command

call "%~dp0tools\windows\setupsymbolpath.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install Python 2.7.7

call "%~dp0tools\windows\setuppython27.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install Perforce Client

call "%~dp0tools\windows\setupperforce.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install Graphviz

call "%~dp0tools\windows\setupgraphviz.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install Doxygen

call "%~dp0tools\windows\setupdoxygen.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install HTML Help Workshop

call "%~dp0tools\windows\setuphtmlhelp.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install DirectX SDK June 2010

call "%~dp0tools\windows\setupdirectxsdk.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install Open Watcom

call "%~dp0tools\windows\setupwatcom.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install CodeBlocks

call "%~dp0tools\windows\setupcodeblocks.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Install GitExtensions

call "%~dp0tools\windows\setupgitextensions.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Locate Codewarrior 9.4 for Windows if present

call "%~dp0tools\windows\setupcodewarrior.cmd"
if not %errorLevel% == 0 goto scriptfailure

:: Set up the path to point to SDKS\Windows\Bin\x64 and x86

call "%~dp0tools\windows\setuppath.cmd"
if not %errorLevel% == 0 goto scriptfailure

echo Your system is all set for building Burgerlib based code!

exit /b

:: Script failure?
:scriptfailure
pause
exit /b 10




