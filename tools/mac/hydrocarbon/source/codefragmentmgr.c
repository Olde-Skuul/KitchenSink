/***************************************

	HydroCarbon post linker
	This is a fake CodeFragmentMgr library so the
	application can load initially and then it's fixed
	up later in hydrocarbonpost.c
	
	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com
 
	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!
	
***************************************/

#include <CodeFragments.h>

#define CloseConnection FloseConnection
#define GetDiskFragment FetDiskFragment

#if 0
pascal __declspec(dllexport) OSErr CountSymbols(CFragConnectionID connID,long *symCount)
{
	return noErr;
}

pascal __declspec(dllexport) OSErr GetMemFragment(void *memAddr,UInt32 length,ConstStr63Param fragName,
	CFragLoadOptions options,CFragConnectionID *connID,
	Ptr *mainAddr,Str255 errMessage)
{
	return noErr;
}

pascal __declspec(dllexport) OSErr FindSymbol(CFragConnectionID connID,ConstStr255Param symName,
	Ptr *symAddr,CFragSymbolClass *symClass)
{
	return noErr;
}

pascal __declspec(dllexport) OSErr GetIndSymbol(CFragConnectionID connID,long symIndex,
	Str255 symName,Ptr *symAddr,CFragSymbolClass *symClass)
{
	return noErr;
}

pascal __declspec(dllexport) OSErr GetSharedLibrary(ConstStr63Param libName,CFragArchitecture archType,
	CFragLoadOptions options,CFragConnectionID *connID,Ptr *mainAddr,Str255 errMessage)
{
	return noErr;
}
#endif

pascal __declspec(dllexport) OSErr CloseConnection(CFragConnectionID * connID)
{
	return noErr;
}

pascal __declspec(dllexport) OSErr GetDiskFragment(const FSSpec *fileSpec,UInt32 offset,
	UInt32 length,ConstStr63Param fragName,CFragLoadOptions options,
	CFragConnectionID *connID,Ptr *mainAddr,Str255 errMessage)
{
	return noErr;
}
