/***************************************

	Print the time in English (TM)

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

***************************************/

#include "tyme.h"
#include <stdio.h>

/***************************************

	System variables

***************************************/

static const char *Justs[5] = {"","just past ","just after ","nearly ","almost "};
static const char *Min5[] = {"","five","ten","a quarter","twenty","twenty-five","half"};
static const char *Numbers[] = {"twelve","one","two","three","four","five","six",
					"seven","eight","nine","ten","eleven"};
static const char *Monthstxt[] = {"January","February","March","April","May","June","July",
					"August","September","October","November","December"};
static const char *Daze[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

/***************************************

	Print the time in English (TM)

***************************************/

static void PrintTime(char *pOutput,const TimeDate_t *pNewTime)
{
	char MyStr[20];		// Temp text string

	Word uSeconds = pNewTime->m_bSecond;	// Get the time from the structure
	Word uMinutes = pNewTime->m_bMinute;	// So that it is accessed from the CPU's best
	Word uHour = pNewTime->m_bHour;			// mode (16 bit for 65816 / 32 for ARM 6)

	if (uSeconds>=30) {			// Adjust for half minutes
		uMinutes++;				// Add a minute for half minute
	}
	if (uMinutes>=33) {			// Adjust for close to the hour
		uHour++;				// Add an hour for half hour
	}

	StringCopy(pOutput,"Good ");	// Start the sentence
	if (uHour<12) {					// Is this the morning?
		StringConcatenate(pOutput,"morning");
	} else if (uHour<18) {			// Night?
		StringConcatenate(pOutput,"afternoon");
	} else {
		StringConcatenate(pOutput,"evening");
	}

	StringConcatenate(pOutput,"! It's ");			// Start the message
	StringConcatenate(pOutput,Justs[uMinutes%5]);	// Minutes adjust

	Word uTemp;
	if (uMinutes<30) {			// +2 in either case to fine adjustment
		uTemp = uMinutes+2;		// Minutes past the hour
	} else {
		uTemp = 62-uMinutes;	// Minutes toward the hour (Negated 60-)
	}
	StringConcatenate(pOutput,Min5[uTemp/5]);		// How many minutes in groups of 5

	if ((uMinutes>=3) && (uMinutes<58)) {			// No message if too close to the hour
		if (uMinutes<33) {
			StringConcatenate(pOutput," past ");	// Past the hour
		} else {
			StringConcatenate(pOutput," to ");		// Toward the hour
		}
	}
	uHour%=12;		// Convert to 12 hour clock (Not 24 hour)
	StringConcatenate(pOutput,Numbers[uHour]);		// Print the hour

	if ( (!uMinutes) || (uMinutes == 60)) {	// On the hour?
		if (!uHour) {						// Noon?
			StringConcatenate(pOutput," noon"); 	// twelve noon
		} else {
			StringConcatenate(pOutput," o'clock");	// nine o'clock
		}
	}
	StringConcatenate(pOutput," on ");			// Day
	StringConcatenate(pOutput,Daze[pNewTime->m_bDayOfWeek]);
	StringConcatenate(pOutput," ");				// Space
	StringConcatenate(pOutput,Monthstxt[pNewTime->m_bMonth-1]);	// Month
	sprintf(MyStr," %d, %d.\n",pNewTime->m_bDay,pNewTime->m_uYear);	// Day and year
	StringConcatenate(pOutput,MyStr);				// Save my final result
}

/***************************************

	Print the today message

***************************************/

int BURGER_ANSIAPI main(int argc,const char * /* argv */ [])
{
	char TempString[130];
	TimeDate_t TheTime;

	if (argc!=1) {
		printf("Copyright 1990,1993 Rebecca Ann Heineman\n");
	}

	TheTime.GetTime();
	PrintTime(TempString,&TheTime);  /* Print the time in English (TM) */
	printf(TempString);					/* Print it */
	return 0;
}
