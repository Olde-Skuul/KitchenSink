/***************************************

	Simple utility to add linefeeds to a Macintosh
	or Apple II type text file for use on Messy DOS machines

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

***************************************/

#ifndef __ADDLF_H__
#define __ADDLF_H__

#ifndef __BURGER__
#include <burger.h>
#endif

//
// Which text file type to support
//

enum eTextType {
	TEXTTYPE_WINDOWS,
	TEXTTYPE_MACOS,
	TEXTTYPE_LINUX
};

extern Word BURGER_API ConvertLineEndings(OutputMemoryStream *pOutput,const char *pInput,WordPtr uLength,eTextType eType);
extern Word BURGER_API AddLF(Filename *pInputFilename,Filename *pOutputFilename,eTextType eType);
extern int BURGER_ANSIAPI main(int argc,const char **argv);

#endif
