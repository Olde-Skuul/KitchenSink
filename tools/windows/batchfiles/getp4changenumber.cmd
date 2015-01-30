@echo off

:: Call the python script "getp4changenumber.py" as a windows batch file

:: Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

:: It is released under an MIT Open Source license. Please see LICENSE
:: for license details. Yes, you can use it in a
:: commercial title without paying anything, just give me a credit.
:: Please? It's not like I'm asking you for money!

:: Locate where Python is stored

if not "%PYTHON%" == "" goto pythonvarpresent
	set PYTHON=%SystemDrive%\Python27
:pythonvarpresent

:: Ensure the python library path is set

if not "%PYTHONPATH%" == "" goto pythonpathpresent

:: Test for the presence of the build file and set the path there
	if not exist %~dp0..\..\..\python\build.py goto notpresent1
	call :expandpythonpath %~dp0..\..\..\python
	goto pythonpathpresent
:notpresent1
	if not exist %~dp0..\..\..\sdks\python\build.py goto notpresent2
	call :expandpythonpath %~dp0..\..\..\sdks\python
	goto pythonpathpresent

:: Fallback
:notpresent2
	set PYTHONPATH=%SDKS%\python
:pythonpathpresent

:: Call the python script

"%PYTHON%\python.exe" "%SDKS%\python\getp4changenumber.py" %*
exit /b %ERRORLEVEL%

:: Set the variable PYTHONPATH

:expandpythonpath
set PYTHONPATH=%~f1
exit /b
