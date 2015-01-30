Any problems or questions regarding this release should be directed to:

dhuffman@clearwater.net

---------
                             GENERAL INSTALLATION

The online X-32VM users manual consists of upshot.exe and x32-vm.mnl.  To read 
the manual from a DOS prompt enter:

upshot X-32vm.mnl

This provides a full description of the 32 bit API and various issues 
surrounding program development of DOS extended applications.

---------
             Linking X-32 programs with the Digital Mars Compiler

Copy the X-32 lib directory files (X32.LIB, X32V.LIB, CX.OBJ, and ZLX.LOD) 
from the X-32 directory to the DM LIB directory.

The actual DOS extender (in the LIB directory) is composed of ZLX.LOD, CX.OBJ,
X32.LIB, and X32V.LIB.  

Build X-32 applications via the following command line:

        SC MY_PROG.C -mx X32.LIB

        or for virtual memory support on non-DPMI systems:

        SC MY_PROG.C -mx X32V.LIB


-------------
Release notes: April 2, 2001

Released support for the Digital Mars compiler.


-------------
Release notes: May 15, 2001

This is the first new release of X32 since November 1995.

Only minor changes have been made.   This includes:

1.  X-32 now knows how to allocate more than 64 megabytes from himem.sys.

2.  A bug was fixed in int 21h function 250Bh.

3.  A bug was fixed in int 21h function 350Eh.
