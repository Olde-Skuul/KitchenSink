/***************************************

	Print the time in English (TM)

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

***************************************/

#include "time2.h"
#include <stdio.h>

/***************************************

	Main entry point

	Unit test for Burgerlib clock functions

***************************************/

int BURGER_ANSIAPI main(int argc,const char ** /* argv */)
{
	if (argc!=1) {
		printf("Copyright by Rebecca Ann Heineman\n");
	}

	TimeDate_t TheTime;
	char TimeString[256];
	char DateString[256];

	TheTime.GetTime();
	TheTime.DateToStringVerbose(DateString);
	TheTime.TimeToString(TimeString);
	printf("%s %s\n",DateString,TimeString);
	return 0;
}
