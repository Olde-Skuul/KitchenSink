/***************************************

	Convert a binary file into an ASCII text
	dump. The dump can be formatted into "C"
	source files.

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!
	
***************************************/

#ifndef __DUMP_H__
#define __DUMP_H__

#ifndef __BURGER__
#include <burger.h>
#endif

//
// Console App definition
//

class DumpConsoleApp : public ConsoleApp {
public:
	enum {
		DUMP_HEX,
		DUMP_ASM,
		DUMP_C,
		DUMP_INTEL,
		DUMP_MOSTEK
	};
	enum {
		BUFFER_SIZE=0x4000
	};

	Word m_uHexSource;	// 0 = Hex dump, 1 = ASM dump, 2 = C source dump
	WordPtr m_uStart;	// Starting file offset
	WordPtr m_uLength;	// Ending file offset
	WordPtr m_uMaxLine;	// Maximum single line length
	Word m_bShowASCII;	// If true, then show ASCII after hex dump
public:
	DumpConsoleApp(int iArgc,const char **ppArgv) :
		ConsoleApp(iArgc,ppArgv) {}
	void BURGER_API DumpHexSource(const Word8 *pBuffer,WordPtr uCount) const;
	void BURGER_API DumpCSource(const Word8 *pBuffer,WordPtr uCount) const;
	void BURGER_API DumpHex(const Word8 *pBuffer,WordPtr uStart,WordPtr uCount) const;
	void BURGER_API DumpMostek(const Word8 *pBuffer,WordPtr uStart,WordPtr uCount) const;
	void BURGER_API DumpIntel(const Word8 *pBuffer,WordPtr uStart,WordPtr uCount) const;
};

#endif
