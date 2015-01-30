@echo off

:: Call the Xbox 360 disassembler

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

"%xedk%\bin\win32\dumpbin.exe" /disasm %*
exit /b %ERRORLEVEL%
