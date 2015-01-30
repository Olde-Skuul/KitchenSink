KitchenSink
===========

Main Build environment for Olde Sküül projects

This repository contains all of the build scripts,
Xcode/Visual Studio/Watcom etc config files and
prebuilt libraries and headers for linking
all projects that depend on the Burgerlib suite
of libraries.

The environment variable SDKS needs to be set to
the folder this file is occupying. All projects
use this as the root and will point to the
requested folders they desire from it.

Setting up for the building of the code.
----------------------------------------

Run setuppc.bat for PC hosts and setupmac.sh for mac
hosts so that environment variables are properly set
up and prerequiste software is detected.

PC software prerequisites
-------------------------

Perforce client and the environment variable PERFORCE set to the path (Example PERFORCE=C:\Program Files\Perforce)
Visual Studio 2010 and the environment variable VS100COMNTOOLS (Set up by default with the installation of Visual Studio 2010)
Doxygen and the environment variable DOXYGEN (Example DOXYGEN=C:\Program Files\doxygen)
Graphviz and the environment variable GRAPHVIZ (Example GRAPHVIZ=C:\Program Files (x86)\Graphviz 2.28)
Python 2.7.3 (Or higher) from Python.org and .py files associated with it

Optional installs
The Xbox 360 XDK
The Xbox ONE XDK
The Xbox XDK and Visual Studio 2003
Codewarrior 9.2 for Windows
Codewarrior for Wii
Codewarrior for Nintendo DS
The PS3 SDK
The PS4 SDK
The nVidia Shield SDK
The OUYA SDK
The Android NDK
Watcom C from http://www.openwatcom.org

Environent variables that the build tools use (And detect)

DOXYGEN=C:\Program Files\doxygen
GRAPHVIZ=C:\Program Files (x86)\GraphViz2.38
PYTHON=C:\Python27
P4CONFIG=p4config

XDK=C:\Program Files (x86)\Microsoft Xbox SDK
XEDK=C:\Program Files (x86)\Microsoft Xbox 360 SDK
VS100COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools\
VS110COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\
VS71COMNTOOLS=c:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Common7\Tools\
VS80COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio 8\Common7\Tools\
VS90COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\
WATCOM=C:\WATCOM
CWFolder=C:\Program Files (x86)\Metrowerks\CodeWarrior
NV=c:\nvpack
PERFORCE=C:\Program Files\Perforce
_NT_SYMBOL_PATH=symsrv*symsrv.dll*%TEMP%\localsymbols*http://msdl.microsoft.com/download/symbols


Mac OSX software prerequisites
------------------------------

Doxygen in the Applications folder
XCode 5 in the Applications folder
Python 2.7.3 (Or higher) from Python.org and .py files associated with it

Optional installs
XCode 3.1.4 in the /XCode 3.1.4 folder (For building PowerPC code)
Codeblocks from http://www.codeblocks.org

Perforce integration
--------------------

The parent source tree is hosted on a Perforce server and then
pushed to Git hosted on SourceForge and GitHub

p4config contains the information for perforce's automated scripts to update the source repository.
Modify these three entries to contain the local machines credentials.

Note: On Mac OSX and Linux hosts, make sure that the p4config file uses Linux/Unix style line feeds
or the p4 tool will silently fail.

p4port=
p4user=
p4passwd=
p4client=

Feedback
--------

BurgerLib is copyright 1995-2014 by Rebecca Ann Heineman <becky@burgerbecky.com>.

Send all suggestions, corrections, optimizations and insults to her and she'll be eternally grateful.
