/***************************************
	
	HydroCarbon Altivec dispatcher
	(This code can be linked to either Classic
	or Carbon without changes)

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com
 
	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!
	
***************************************/

#include <Gestalt.h>
#include <CodeFragments.h>

extern pascal OSErr initialize(const CFragInitBlock *initBlock);
extern pascal int start(void);
extern pascal void terminate(void);

/***************************************

	I will choose between an AltiVec and
	a standard version of an application
	(This can be linked to classic or Carbon)
		
***************************************/

static CFragConnectionID MyConnectionID;
static int (*MyMainProc)(void);
static long NormalOffset = 0xD5AA9601;		/* These will be patched by HydroCarbon */
static long NormalLength = 0xD5AA9602;
static long AltivecOffset = 0xD5AA9603;
static long AltivecLength = 0xD5AA9604;

/***************************************

	This is called on start up, Here, I will do the test
	for AltiVec and load the proper library (Application)
		
***************************************/

pascal OSErr initialize(const CFragInitBlock *initBlock)
{
	long Offset,Length;
	long ppcFeatures;
	
	Length = NormalLength;
	Offset = NormalOffset;
	if (!Gestalt(gestaltPowerPCProcessorFeatures, &ppcFeatures)) {
		if (ppcFeatures & (1<<gestaltPowerPCHasVectorInstructions)) {
			Length = AltivecLength;
			Offset = AltivecOffset;
		}
	}
	return GetDiskFragment(initBlock->fragLocator.u.inSegs.fileSpec,Offset,Length,
		0,kDataForkCFragLocator,&MyConnectionID,(Ptr *)&MyMainProc,0);
}

/***************************************

	Called when the application is to start
		
***************************************/

pascal int start(void)
{
	if (MyMainProc) {
		return MyMainProc();		/* Call the app */
	}
	return 0;		/* Oh oh */
}

/***************************************

	Perform cleanup
		
***************************************/

pascal void terminate(void)
{
	if (MyConnectionID) {		/* Do I have a connection? */
		CloseConnection(&MyConnectionID);
		MyConnectionID = 0;
	}
}

