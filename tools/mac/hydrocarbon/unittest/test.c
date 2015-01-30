/***************************************

	This is a test application to test all features of Burgerlib net
	Must be compiled under SOIUX for Win95 interaction
	All others use an ANSI console

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com
 
	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

***************************************/

#include <burger.h>
#include <stdlib.h>

/***************************************

	Test burgerlib Network

***************************************/

int main(void)
{
	Globals::SetTraceFlag(Globals::TRACE_THEWORKS);
	Globals::SetErrorBombFlag(FALSE);
	ConsoleApp(0,0);

#if defined(__POWERPC__)
#if TARGET_API_MAC_CARBON
	Debug::Message("Carbon\n");
#else
	Debug::Message("Classic\n");
#endif
#else
	Debug::Message("68000 version\n");
#endif
	return 0;
}


