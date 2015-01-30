/**********************************

	Copyright 1999-2007 
	Rebecca Ann Heineman
	
	Resource data to announce that I'm a post linker
	for Hydrocarbon
	
**********************************/

#include "CWPlugins.r"
#include "MacTypes.r"

resource 'Flag' (128,"HydroCarbon") {
	Linker {
		8,			// Version 8.0 or later
		cantDisassemble,
		isPostLinker,
		allowDuplicateFileNames,
		isntMultipleTargetAware,
		isntPreLinker,
		doesntUseTargetStorage,
		doesntUnmangleNames,
		isntMagicCapLinker,
		dontAlwaysReload,
		doesntWantBuildStartedRequest,
		doesntWantTargetBuildStartedRequest,
		doesntWantSubprojectBuildStartedRequest,
		0,doesntWantTargetLinkStartedRequest,
		doesntWantPreRunRequest,
		isntThreadSafe,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,			// Reserved long
		8,			// API version 8.0 supported.
		0,			// Reserved
		0			// Reserved
	}
};

resource 'STR ' (128, "HydroCarbon Name") {
	"HydroCarbon Post-Linker"
};

resource 'Targ' (128,"HydroCarbon") {
	kCurrentResourceVersion,
	{Any},
	{MacOS} 
};

resource 'vers' (1) {
	0x01,		// Major version
	0x10,		// Minor version
	final,
	0,
	verUS,
	"1.1",
	"1.1 \0xA9 2001-2007 Rebecca Ann Heineman"
};

resource 'vers' (2) {
	0x01,		// Major version
	0x10,		// Minor version
	final,
	0,
	verUS,
	"1.1",
	"1.1 \0xA9 2001-2007 Rebecca Ann Heineman"
};
