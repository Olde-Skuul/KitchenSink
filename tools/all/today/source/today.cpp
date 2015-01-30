/***************************************

	Today, a simple tool to print out today's events
	Based on source from Patrick Kincaid 

	Copyright 1986-2015 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

	Documentation can be found at http://www.burgerbecky.com/burgerlib/docs

	Comments, suggestions, bug fixes, email me at becky@burgerbecky.com

***************************************/

#include <burger.h>

#if defined(BURGER_APPLEIIGS)
#pragma optimize -1
#endif

//
// Header for each date entry
//
// B01011735 Paul Revere
//
// B01101877 Frederick Gardner Cottrell, invented the electrostatic
// B01101877Cprecipitator, used for pollution control and air ionizers.
//

struct EntryRecord_t {
	char m_cRecordType;		// Type of record
	char m_MonthDigits[2];	// Month to scan
	char m_DayDigits[2];	// Day to scan
	char m_YearDigits[4];	// Year to print
	char m_cContinue;		// Continue code
	const char *m_pText;	// Pointer to text (Not zero terminated)
	WordPtr m_uTextLength;	// Length of the text
};

struct MatchRecord_t {
	char m_cRecordType;		// Type of record
	char m_MonthDigits[2];	// Month to scan
	char m_DayDigits[2];	// Day to scan
};

/***************************************

	System variables

***************************************/

static const char *g_Justs[5] = {"","just past ","just after ","nearly ","almost "};
static const char *g_Min5[] = {"","five","ten","a quarter","twenty","twenty-five","half"};
static const char *g_Numbers[] = {"twelve","one","two","three","four","five","six",
					"seven","eight","nine","ten","eleven"};

// Buffer for the output string
static char WorkBuffer[8000];

/***************************************

	Print the time in English (TM)

***************************************/

static void PrintTime(char *pOutput,WordPtr uOutputSize,const TimeDate_t *pCurrentTime)
{
	Word uSeconds = pCurrentTime->m_bSecond;	// Get the time from the structure
	Word uMinutes = pCurrentTime->m_bMinute;	// So that it is accessed from the CPU's best
	Word uHour = pCurrentTime->m_bHour;		// mode (16 bit for 65816 / 32 for ARM 6)

	if (uSeconds>=30U) {				// Adjust for half minutes
		uMinutes++;						// Add a minute for half minute
	}
	if (uMinutes>=33U) {				// Adjust for close to the hour
		uHour++;						// Add an hour for half hour
	}

	StringCopy(pOutput,"Good ");		// Start the sentence
	if (uHour<12U) {					// Is this the morning?
		StringConcatenate(pOutput,uOutputSize,"morning");
	} else if (uHour<18U) {				// Night?
		StringConcatenate(pOutput,uOutputSize,"afternoon");
	} else {
		StringConcatenate(pOutput,uOutputSize,"evening");
	}

	StringConcatenate(pOutput,uOutputSize,"! It's ");				// Start the message
	StringConcatenate(pOutput,uOutputSize,g_Justs[uMinutes%5U]);	// Minutes adjust

	Word uTemp;
	if (uMinutes<30U) {			// +2 in either case to fine adjustment
		uTemp = uMinutes+2;		// Minutes past the hour
	} else {
		uTemp = 62-uMinutes;	// Minutes toward the hour (Negated 60-)
	}
	WordPtr uIndex = uTemp/5U;
	if (uIndex>=BURGER_ARRAYSIZE(g_Min5)) {
		uIndex = BURGER_ARRAYSIZE(g_Min5)-1;
	}
	StringConcatenate(pOutput,uOutputSize,g_Min5[uIndex]);		// How many minutes in groups of 5

	// No message if too close to the hour

	if ((uMinutes>=3) && (uMinutes<58)) {						
		if (uMinutes<33) {
			StringConcatenate(pOutput,uOutputSize," past ");	// Past the hour
		} else {
			StringConcatenate(pOutput,uOutputSize," to ");		// Toward the hour
		}
	}
	uHour%=12;		// Convert to 12 hour clock (Not 24 hour)
	StringConcatenate(pOutput,uOutputSize,g_Numbers[uHour]);	// Print the hour

	if ( (!uMinutes) || (uMinutes == 60)) {			// On the hour?
		if (!uHour) {								// Noon?
			StringConcatenate(pOutput,uOutputSize," noon"); 	// twelve noon
		} else {
			StringConcatenate(pOutput,uOutputSize," o'clock");	// nine o'clock
		}
	}
	StringConcatenate(pOutput,uOutputSize," on ");			// Day
	StringConcatenate(pOutput,uOutputSize,g_WeekDays[pCurrentTime->m_bDayOfWeek]);
	StringConcatenate(pOutput,uOutputSize," ");				// Space
	StringConcatenate(pOutput,uOutputSize,g_Months[pCurrentTime->m_bMonth-1]);		// Month
	StringConcatenate(pOutput,uOutputSize," ");				// Space

	NumberString DayString(static_cast<Word32>(pCurrentTime->m_bDay));
	StringConcatenate(pOutput,uOutputSize,DayString);		// Day

	StringConcatenate(pOutput,uOutputSize,", ");			// Separator
	NumberString YearString(static_cast<Word32>(pCurrentTime->m_uYear));
	StringConcatenate(pOutput,uOutputSize,YearString);		// Year
	StringConcatenate(pOutput,uOutputSize,".\n");			// Save my final result 
}

/***************************************

	Find the next matching entry
	return TRUE if the EntryRecord is valid, FALSE if end of file

***************************************/

static Word ScanString(EntryRecord_t *pOutput,const char **ppText,WordPtr *pRemaining,const MatchRecord_t *pMatch)
{
	// Assume failure
	pOutput->m_pText = NULL;
	pOutput->m_uTextLength = 0;

	const char *pText = *ppText;			// Get handle to my pointer
	WordPtr uRemaining = *pRemaining;
	Word uResult = FALSE;
	if (pText && uRemaining) {				// Valid pointer and buffer size?

		for(;;) {							// Forever?

			// Is there enough memory for a header?
			if (uRemaining<10) {
				// Force abort
				uRemaining = 0;
				break;
			}

			// Determine the length of this line
			const char *pMark = pText;
			pText = ParseBeyondEOL(pText,uRemaining);

			// Can only match if there's a zero in the stream.
			// If there's a zero, abort
			if (pText==pMark) {
				uRemaining = 0;
				break;
			}

			// Accept the data
			WordPtr uLineLength = (pText-pMark);
			uRemaining -= uLineLength;

			if (pMark[uLineLength-1]=='\r') {
				--uLineLength;
			} else if (pMark[uLineLength-1]=='\n') {
				if (--uLineLength) {
					if (pMark[uLineLength-1]=='\r') {
						--uLineLength;
					}
				}
			}

			// Is this not a comment?
			if (uLineLength>=10) {			// Skip comments
				Word uTemp = pMark[0];		// Get the first char
				if (uTemp == 'Z') {			// End of the list?
					uRemaining = 0;			// Force abort
					break;
				}

				// Copy the header
				pOutput->m_cRecordType = static_cast<char>(uTemp);
				pOutput->m_MonthDigits[0] = pMark[1];
				pOutput->m_MonthDigits[1] = pMark[2];
				pOutput->m_DayDigits[0] = pMark[3];
				pOutput->m_DayDigits[1] = pMark[4];
				pOutput->m_YearDigits[0] = pMark[5];
				pOutput->m_YearDigits[1] = pMark[6];
				pOutput->m_YearDigits[2] = pMark[7];
				pOutput->m_YearDigits[3] = pMark[8];
				pOutput->m_cContinue = pMark[9];

				// Is this an entry that should be printed?
				if ((pOutput->m_cRecordType == pMatch->m_cRecordType) &&
					((pOutput->m_MonthDigits[0] == '0' && pOutput->m_MonthDigits[1]=='0') || (pOutput->m_MonthDigits[0] == pMatch->m_MonthDigits[0] && pOutput->m_MonthDigits[1]==pMatch->m_MonthDigits[1])) &&
					((pOutput->m_DayDigits[0] == '0' && pOutput->m_DayDigits[1] == '0') || (pOutput->m_DayDigits[0] == pMatch->m_DayDigits[0] && pOutput->m_DayDigits[1] == pMatch->m_DayDigits[1]))) {
					pOutput->m_pText = pMark+10;	// Index to the actual text
					pOutput->m_uTextLength = uLineLength-10;
					uResult = TRUE;					// I have a valid entry!
					break;
				}
			}
		}

		// Mark the position
		*ppText = pText;			
		*pRemaining = uRemaining;	// Set the remaining data
	}
	return uResult;
}

/***************************************

	Print all messages that pertain to today's date

***************************************/

static void PrintBirthdays(char *pOutput,WordPtr uOutputLength,MatchRecord_t *pMatch,const char *pInput,WordPtr uInputLength)
{
	EntryRecord_t BirthRecord;
	pMatch->m_cRecordType = 'B';
	// Check for the next line of text
	while (ScanString(&BirthRecord,&pInput,&uInputLength,pMatch)) {
		// Is it continue?
		if (BirthRecord.m_cContinue!='C') {			
			StringConcatenate(pOutput,uOutputLength,"   In ");
			if (BirthRecord.m_YearDigits[3] == ' ') {
				StringConcatenate(pOutput,uOutputLength,"????");
			} else {
				StringConcatenate(pOutput,uOutputLength,BirthRecord.m_YearDigits,4);
			}
			StringConcatenate(pOutput,uOutputLength," ");
		}
		StringConcatenate(pOutput,uOutputLength,BirthRecord.m_pText,BirthRecord.m_uTextLength);
		StringConcatenate(pOutput,uOutputLength,"\n");
	}
}

/***************************************

	Print all messages that pertain to today's date

***************************************/

static void PrintEvents(char *pOutput,WordPtr uOutputLength,MatchRecord_t *pMatch,const char *pInput,WordPtr uInputLength)
{
	EntryRecord_t EventRecord;
	pMatch->m_cRecordType = 'S';
	// Check for the next line of text
	while (ScanString(&EventRecord,&pInput,&uInputLength,pMatch)) {
		// Is it continue?
		if (EventRecord.m_cContinue!='C') {
			if (EventRecord.m_YearDigits[3] != ' ') {
				StringConcatenate(pOutput,uOutputLength,"   In ");
				StringConcatenate(pOutput,uOutputLength,EventRecord.m_YearDigits,4);
				StringConcatenate(pOutput,uOutputLength," ");
			}
		}
		StringConcatenate(pOutput,uOutputLength,EventRecord.m_pText,EventRecord.m_uTextLength);
		StringConcatenate(pOutput,uOutputLength,"\n");
	}
}

/***************************************

	Print all messages that pertain to today's date

***************************************/

static void PrintReminders(char *pOutput,WordPtr uOutputLength,MatchRecord_t *pMatch,const char *pInput,WordPtr uInputLength)
{
	EntryRecord_t ReminderRecord;
	pMatch->m_cRecordType = 'R';
	// Check for the next line of text
	while (ScanString(&ReminderRecord,&pInput,&uInputLength,pMatch)) {
		StringConcatenate(pOutput,uOutputLength,ReminderRecord.m_pText,ReminderRecord.m_uTextLength);
	}
}

/***************************************

	Print the today message

***************************************/

int BURGER_ANSIAPI main(int argc,const char **argv)
{
	ConsoleApp MyApp(argc,argv);
	TimeDate_t MyTime;	// Current time

	MyTime.GetTime();	// Get the current time

	String TodayFileName("9:today.txt");		// Filename to load
	WordPtr uDataLength;
	char *pDataFile = static_cast<char *>(FileManager::LoadFile(TodayFileName,&uDataLength));

	// Read in my extra file
	WordPtr uUserLength;
	char *pUserFile = static_cast<char *>(FileManager::LoadFile("9:today.own",&uUserLength));

	// Print the time in English (TM)
	PrintTime(WorkBuffer,BURGER_ARRAYSIZE(WorkBuffer),&MyTime);
	StringConcatenate(WorkBuffer,BURGER_ARRAYSIZE(WorkBuffer),"\n");
	fwrite(WorkBuffer,1,StringLength(WorkBuffer),stdout);


	// Convert day and month to 2 char values
	MatchRecord_t Match;
	Word uTemp = MyTime.m_bDay;
	Match.m_DayDigits[1] = static_cast<char>(uTemp%10 + '0');
	Match.m_DayDigits[0] = static_cast<char>(uTemp/10 + '0');
	uTemp = MyTime.m_bMonth;
	Match.m_MonthDigits[1] = static_cast<char>(uTemp%10 + '0');
	Match.m_MonthDigits[0] = static_cast<char>(uTemp/10 + '0');

	// Blank out the string
	WorkBuffer[0] = 0;
	PrintBirthdays(WorkBuffer,BURGER_ARRAYSIZE(WorkBuffer),&Match,pDataFile,uDataLength);
	PrintBirthdays(WorkBuffer,BURGER_ARRAYSIZE(WorkBuffer),&Match,pUserFile,uUserLength);
	if (WorkBuffer[0]) {
		puts("Happy Birthday to...");
		puts(WorkBuffer);
	}

	// Blank out the string
	WorkBuffer[0] = 0;
	PrintEvents(WorkBuffer,BURGER_ARRAYSIZE(WorkBuffer),&Match,pDataFile,uDataLength);
	PrintEvents(WorkBuffer,BURGER_ARRAYSIZE(WorkBuffer),&Match,pUserFile,uUserLength);
	if (WorkBuffer[0]) {
		puts("On this day...");
		puts(WorkBuffer);
	} else {
		puts("Nothing much happened.");
	}
	
	// Blank out the string
	WorkBuffer[0] = 0;
	PrintReminders(WorkBuffer,BURGER_ARRAYSIZE(WorkBuffer),&Match,pUserFile,uUserLength);
	if (WorkBuffer[0]) {
		puts("Did you remember?");
		puts(WorkBuffer);
	}
	// Release the files
	Free(pDataFile);
	Free(pUserFile);
	return 0;
}
