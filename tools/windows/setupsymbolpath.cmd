@echo off

:: Enable Visual studio to pull microsoft symbols from the symbol server
:: by setting _NT_SYMBOL_PATH

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: Is the path already set?

if not "%_NT_SYMBOL_PATH%" == "" goto symbolsfound

:: Create the local symbols folder if one doesn't already exist

	if exist "%temp%\localsymbols" goto nolocalsymbolsfolder
		echo Creating "%temp%\localsymbols"
		md "%temp%\localsymbols"
	:nolocalsymbolsfolder

:: Set the environment variable

	echo Setting _NT_SYMBOL_PATH="symsrv*symsrv.dll*%temp%\localsymbols*http://msdl.microsoft.com/download/symbols"
	setx _NT_SYMBOL_PATH "symsrv*symsrv.dll*%temp%\localsymbols*http://msdl.microsoft.com/download/symbols"
	set _NT_SYMBOL_PATH=symsrv*symsrv.dll*%temp%\localsymbols*http://msdl.microsoft.com/download/symbols
:symbolsfound
exit /b 0
