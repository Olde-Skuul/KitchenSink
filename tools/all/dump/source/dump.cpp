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

#include "dump.h"

/***************************************

	Print the range as asm hex source output
	The text takes the form of...
	\tDB\t0xxH,0xxH,0xxH,0xxH\n

***************************************/

void BURGER_API DumpConsoleApp::DumpHexSource(const Word8 *pBuffer,WordPtr uCount) const
{
	do {
		// Get the length of this run
		WordPtr uSize = (uCount<m_uMaxLine) ? uCount : m_uMaxLine;

		printf("\tDB\t");	// ASM command
		Word i = 0;
		do {
			if (i) {		// Don't print the first time
				putchar(',');
			}
			putchar('0');	// Print in the format 0xxH
			PrintHex(pBuffer[0]);
			++pBuffer;
			putchar('H');	// Finish the hex value
		} while (++i<uSize);
		putchar('\n');		// Terminate the line
		uCount-=uSize;
	} while (uCount);		// Next line
}

/***************************************

	Print the range as "C" hex source output
	The text takes the form of...
	\t0xXX,0xXX,0xXX,0xXX,\n

	Note: If this is the last dump, the final comma is
	eliminated.

***************************************/

void BURGER_API DumpConsoleApp::DumpCSource(const Word8 *pBuffer,WordPtr uCount) const
{
	Word uMore = uCount!=m_uLength;
	do {
		// Get the length of this run
		WordPtr uSize = (uCount<m_uMaxLine) ? uCount : m_uMaxLine;
		uCount-=uSize;

		// Line prefix
		putchar('\t');
		Word i = 0;
		do {
			if (i) {		// Don't print the first time
				putchar(',');
			}
			putchar('0');
			putchar('x');
			PrintHex(pBuffer[0]);
			++pBuffer;
		} while (++i<uSize);
		// Do I print the trailing comma?
		if (uCount || uMore) {
			putchar(',');
		}
		putchar('\n');
	} while (uCount);
}

/***************************************

	Perform a raw hex dump

***************************************/

void BURGER_API DumpConsoleApp::DumpHex(const Word8 *pBuffer,WordPtr uStart,WordPtr uCount) const
{
  	WordPtr uSize;
	WordPtr i;
	do {
		PrintHex(static_cast<Word32>(uStart));
		printf(": ");	/* Print the offset */
		uSize = (uCount<m_uMaxLine) ? uCount : m_uMaxLine;	/* Get the smaller */

		i = 0;
		do {
			PrintHex(pBuffer[i]);		// Print the ASCII
			putchar(' ');
		} while (++i<uSize);
		if (m_bShowASCII) {
			if (uSize!=m_uMaxLine) {
				i = m_uMaxLine-uSize;
				do {
					printf("   ");
				} while (--i);
			}
			i = 0;
			do {
				Word Temp;
				Temp = pBuffer[i]&0x7F;
				if (Temp<32) {
					Temp = '.';
				}
				putchar(Temp);
			} while (++i<uSize);
		}
		putchar('\n');
		pBuffer += uSize;
		uCount-=uSize;
		uStart+=uSize;
	} while (uCount);
}

/***************************************

	Convert the file from BIN to Motorola HEX format
	Format of ;(Packet size)(Rom address)(Bytes)(Checksum)

***************************************/

void BURGER_API DumpConsoleApp::DumpMostek(const Word8 *pBuffer,WordPtr uStart,WordPtr uCount) const
{
	do {
		Word uPacket = 16;
	   	if (uCount<16) {				// Max line size is 16 bytes
			uPacket = static_cast<Word>(uCount);	// Use the total size
		}

		Word uCheckSum = uPacket;	// Init the checksum
		Word i = uStart & 0xFF;
		uCheckSum += i;				// Insert the address in the checksum
		i = (uStart >> 8U) & 0xFF;
		uCheckSum += i;

		putchar(';');							// Write the header
		PrintHex(static_cast<Word8>(uPacket));
		PrintHex(static_cast<Word16>(uStart));
		i = 0;
        do {
        	uCheckSum += pBuffer[i];		// Add the checksum
	        PrintHex(pBuffer[i]);			// Write the data
		} while (++i<uPacket);
		PrintHex(static_cast<Word16>(uCheckSum));	// Send the checksum
		putchar('\n');						// End the line
		uStart += uPacket;					// Adjust the address
    	uCount -= uPacket;					// Remove the data
		pBuffer += uPacket;
	} while (uCount);
}

/***************************************

	Convert the file from BIN to INTEL HEX format
	Format of :(Packet size)(Rom address)(00)(Bytes)(Checksum)

***************************************/

void BURGER_API DumpConsoleApp::DumpIntel(const Word8 *pBuffer,WordPtr uStart,WordPtr uCount) const
{
	do {
		Word uPacket = 16;
    	if (uCount<16) {				// Max size is 16 bytes
			uPacket = (Word) uCount;	// Use the total size
		}

		Word uCheckSum = 0-uPacket;		// Init the checksum
		Word i = uStart & 0xFF;
		uCheckSum -= i;					// Insert the address in the checksum
		i = (uStart >> 8U) & 0xFF;
		uCheckSum -= i;

		putchar(':');							// Write the header
		PrintHex(static_cast<Word8>(uPacket));
		PrintHex(static_cast<Word16>(uStart));
		printf("00");
		i = 0;
        do {
        	uCheckSum -= pBuffer[i];			// Add the checksum
	        PrintHex(pBuffer[i]);				// Write the data
		} while (++i<uPacket);
		PrintHex(static_cast<Word8>(uCheckSum&0xff));	// Send the checksum
		putchar('\n');							// End the line
		uStart += uPacket;						// Adjust the address
		pBuffer += uPacket;
    	uCount -= uPacket;						// Remove the data
	} while (uCount);
}

/***************************************

	Perform a memory dump

***************************************/

int BURGER_ANSIAPI main(int argc,const char **argv)
{
	DumpConsoleApp MyApp(argc,argv);
	#define BUFFERSIZE 0x4000
	Word8 Buffer[BUFFERSIZE];

	// Set up the parameters that could be accepted
	CommandParameterWordPtr Mostek("Output in Mostek ROM format at this address (-mostek [$]4000)","mostek",BURGER_MAXWORDPTR);
	CommandParameterWordPtr Intel("Output in Intel ROM format at this address (-intel [$]256)","intel",BURGER_MAXWORDPTR);
	CommandParameterWordPtr Start("Starting file offset (-s 500)","s",0);
	CommandParameterWordPtr Length("Length to dump (-l 256)","l",BURGER_MAXWORDPTR);
	CommandParameterWordPtr MaxLine("Number of entries per line (-m 16)","m",16,0,BUFFERSIZE);

	CommandParameterBooleanTrue ShowAsm("Save as asm hex source","x");
	CommandParameterBooleanTrue ShowC("Save as \"C\" source","c");
	CommandParameterBooleanTrue ShowASCII("Don't show ASCII after hex dump","a");

	const CommandParameter *MyParms[] = {
		&Mostek,
		&Intel,
		&Start,
		&Length,
		&MaxLine,
		&ShowAsm,
		&ShowC,
		&ShowASCII
	};

	argc = MyApp.GetArgc();
	argv = MyApp.GetArgv();
	argc = CommandParameter::Process(argc,argv,MyParms,sizeof(MyParms)/sizeof(MyParms[0]),
		"Usage: dump InputFile\n\n"
		"Dumps the contents of a file to stdout.\nCopyright by Rebecca Ann Heineman\n",2);
	if (argc<0) {
		Globals::SetErrorCode(10);
	} else {
		MyApp.SetArgc(argc);

		// Determine the type of output
		WordPtr uRomOrigin = 0;
		MyApp.m_uHexSource = DumpConsoleApp::DUMP_HEX;
		if (ShowC.GetValue()) {		// Assume binary dump
			MyApp.m_uHexSource = DumpConsoleApp::DUMP_C;
		}
		if (ShowAsm.GetValue()) {
			MyApp.m_uHexSource = DumpConsoleApp::DUMP_ASM;
		}
		if (Mostek.GetValue()!=BURGER_MAXWORDPTR) {
			uRomOrigin = Mostek.GetValue();
			MyApp.m_uHexSource = DumpConsoleApp::DUMP_MOSTEK;
		}
		if (Intel.GetValue()!=BURGER_MAXWORDPTR) {
			uRomOrigin = Intel.GetValue();
			MyApp.m_uHexSource = DumpConsoleApp::DUMP_INTEL;
		}
		MyApp.m_bShowASCII = !ShowASCII.GetValue();		// Show ASCII
		MyApp.m_uStart = Start.GetValue();			// Offset to the start of the file
		MyApp.m_uLength = Length.GetValue();	// Max length
		MyApp.m_uMaxLine = MaxLine.GetValue();			// 16 samples per line

		//
		// Sanity checks
		//

		if (!MyApp.m_uMaxLine) {
			MyApp.m_uMaxLine = 16;	// Reset to default
		}

		Filename InputName;
		InputName.SetFromNative((argv[1]));
		File Input;
		if (Input.Open(&InputName,File::READONLY)) {
			printf("Can't open the input file %s!\n",argv[1]);
			Globals::SetErrorCode(10);
		} else {

			// Get the file's size
			WordPtr uCount = Input.GetSize();	

			// The start is beyond the end of file?
			if (MyApp.m_uStart<uCount) {

				// Get the maximum bytes to dump based on file length and range

				uCount = uCount-MyApp.m_uStart;
				// Is the requested range beyond the end of file?
				if (MyApp.m_uLength>uCount) {		
					MyApp.m_uLength = static_cast<Word32>(uCount);		// Clamp to end of file
				}

				// No data to show?
				if (MyApp.m_uLength) {

					// Seek to beginning of file
					Input.SetMark(MyApp.m_uStart);	

					// Since each of the parsers can't track CR/LF generation due to
					// maxline length, help them by only passing groups of data in multiples
					// of the max line length. This way, it simplifies the code and
					// keeps the feature intact.

					WordPtr uMaxChunk = (BUFFERSIZE/MyApp.m_uMaxLine)*MyApp.m_uMaxLine;

					// 
					// Main loop to read the file, dump the chunk, and continue.
					//

					do {
						// Size of the chunk to process
						uCount = MyApp.m_uLength;
						if (uCount>uMaxChunk) {
							uCount = uMaxChunk;	// Use the maximum size of the buffer
						}
						Input.Read(Buffer,uCount);	// Read it in

						switch (MyApp.m_uHexSource) {
						case DumpConsoleApp::DUMP_ASM:
							// Print as ASM source
							MyApp.DumpHexSource(Buffer,uCount);
							break;
						case DumpConsoleApp::DUMP_C:
							// Print as C source
							MyApp.DumpCSource(Buffer,uCount);
							break;
						case DumpConsoleApp::DUMP_MOSTEK:
							// Print as Mostek ROM source
							MyApp.DumpMostek(Buffer,uRomOrigin,uCount);
							break;
						case DumpConsoleApp::DUMP_INTEL:
							// Print as Mostek ROM source
							MyApp.DumpIntel(Buffer,uRomOrigin,uCount);
							break;
						default:
							// Standard hex dump
							MyApp.DumpHex(Buffer,MyApp.m_uStart,uCount);
						}
						// Adjust pointers
						uRomOrigin+=uCount;
						MyApp.m_uStart+=static_cast<Word32>(uCount);
						MyApp.m_uLength-=static_cast<Word32>(uCount);
					} while (MyApp.m_uLength);		// Done?
				}
				// Output any wrap up
				switch (MyApp.m_uHexSource) {
				case DumpConsoleApp::DUMP_MOSTEK:
					printf(";00\n");				// Epilogue
					break;
				case DumpConsoleApp::DUMP_INTEL:
					printf(":00000001FF\n");		// Epilogue
					break;
				default:
					break;
				}
			}
			Input.Close();
		}
	}
	return Globals::GetErrorCode();
}
