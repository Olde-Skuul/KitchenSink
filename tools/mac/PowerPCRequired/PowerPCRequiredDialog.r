/***************************************

	PowerPCRequired dialog for the 680x0 application

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just 
	Please? It's not like I'm asking you for money!

***************************************/

#include "Dialogs.r"

/* Dialog item list */

resource 'DITL' (32000,PURGEABLE)  {
	{
		{72,80,92,148},		// Bounds rect
		Button {			// Button item
			enabled,		// Enable for input
			"OK"			// Text for the button
		},
		{12,16,60,212},		// Bounds rect
		StaticText {		// Static text
			disabled,
			"This application requires a PowerPC or Intel processor"
		}
	}
};

/* Main dialog */

resource 'DLOG' (32000,PURGEABLE) {
	{186,206,294,434},
	dBoxProc,			// SImple box
	visible,			// It's visible
	goAway,				// It has a go away box
	0,					// Refcon
	32000,				// DITL ID (Must point to the ID above
	"",					// Title string (Not used in dBoxProc
	centerMainScreen	// Center it on the screen
};


