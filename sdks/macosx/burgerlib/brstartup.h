/***************************************

	Start up code for games based applications
	
	MacOSX version
	
	Copyright (c) 1995-2015 by Rebecca Ann Heineman <becky@burgerbecky.com>

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

***************************************/

#ifndef __BRSTARTUP_H__
#define __BRSTARTUP_H__

#ifndef __BURGER__
#include <burger.h>
#endif

//
// Initialize defaults
//

#if !defined(GAMENAME)
#define GAMENAME "Test Application"
#endif

#if !defined(MEMORYSIZE)
#define MEMORYSIZE Burger::MemoryManagerHandle::DEFAULTMEMORYCHUNK
#endif

#if !defined(HANDLECOUNT)
#define HANDLECOUNT Burger::MemoryManagerHandle::DEFAULTHANDLECOUNT
#endif

#if !defined(MINIMUMRESERVE)
#define MINIMUMRESERVE Burger::MemoryManagerHandle::DEFAULTMINIMUMRESERVE
#endif

/***************************************

	This is the main entry point for a MacOSX version of the game

***************************************/

int BURGER_ANSIAPI main(void);

int BURGER_ANSIAPI main(void)
{
	// Create an application instance

	Burger::MacOSXApp MyApp(MEMORYSIZE,HANDLECOUNT,MINIMUMRESERVE);

	// Error on startup?
	int iResult = Burger::Globals::GetErrorCode();

	if (!iResult) {
	
		// Create the default menu items for
		// a Mac OSX application without
		// a Interface Builder XML file

		// Define BURGER_NOMENUS if the Mac OSX
		// application uses Interface Builder to
		// handle menu generation

#if !defined(BURGER_NOMENUS)
		Burger::Globals::CreateDefaultMenus();
#endif

		iResult = CodeEntry(&MyApp);
	}
	return iResult;
}

#endif

