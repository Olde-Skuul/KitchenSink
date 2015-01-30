/***************************************

	Simple utility to add linefeeds to a Macintosh
	or Apple II type text file for use on Messy DOS machines

	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

***************************************/

#include "addlf.h"

static const char *s_TypeName[] = {
	"Windows",
	"MacOS",
	"Linux"
};

/***************************************

	Convert a Mac/Linux/PC text file into a
	PC format text file (/r/n)

***************************************/

Word BURGER_API ConvertLineEndings(OutputMemoryStream *pOutput,const char *pInput,WordPtr uLength,eTextType eType)
{
	Word uResult = 0;
	if (uLength) {
		do {
			// Grab data from the input stream
			Word uTemp = pInput[0];
			++pInput;
			// Carriage return? 
			// It's a special case since it could be a data pair.
			if (uTemp=='\r') {
				// Test to see if it already has a line feed following
				// If so, leave it alone
				if (uLength>=2 && pInput[0]=='\n') {
					++pInput;
					--uLength;
				}
				uTemp = '\n';			// Follow with a line feed
			}
			if (uTemp=='\n') {
				switch (eType) {
				case TEXTTYPE_WINDOWS:
					// Insert a CR to do a conversion
					uResult = pOutput->Append(static_cast<Word8>('\r'));
				case TEXTTYPE_LINUX:
					uResult |= pOutput->Append(static_cast<Word8>('\n'));
					break;
				default:
					uResult = pOutput->Append(static_cast<Word8>('\r'));
					break;
				}
			} else {
				// Store the character as is
				uResult = pOutput->Append(static_cast<Word8>(uTemp));
			}
			// Break on error
			if (uResult) {
				break;
			}
		} while (--uLength);
	}
	return uResult;
}

/***************************************

	Load in a file, convert the line feeds
	and if it's changed or it's being written
	to a different Filename record,
	it will be saved to disk.

***************************************/

Word BURGER_API AddLF(Filename *pInputFilename,Filename *pOutputFilename,eTextType eType)
{
	// Load the input file
	Word bChanged = FALSE;
	WordPtr uLength;
	const char *pInputBuffer = static_cast<const char*>(FileManager::LoadFile(pInputFilename,&uLength));
	if (!pInputBuffer) {
		printf("Can't open %s!",pInputFilename->GetNative());
	} else {
		OutputMemoryStream Output;
		
		Word uResult = ConvertLineEndings(&Output,pInputBuffer,uLength,eType);
		if (uResult) {
			Globals::SetErrorCode(static_cast<int>(uResult));
			printf("Out of memory!");
		} else {
			// Did the data actually change?
			if ((pInputFilename!=pOutputFilename) || Output.Compare(pInputBuffer,uLength)) {
				printf("Converting %s\n",pInputFilename->GetNative());
				// Get the destination filename
				uResult = Output.SaveFile(pOutputFilename);
				bChanged = TRUE;
				if (uResult) {
					printf("Error in saving %s\n",pOutputFilename->GetNative());
					Globals::SetErrorCode(static_cast<int>(uResult));
				}
			} else {
				printf("File %s was already in %s format\n",pInputFilename->GetNative(),s_TypeName[eType]);
			}
		}
		Free(pInputBuffer);
	}
	return bChanged;
}

/***************************************

	Scan a directory, using a wildcard and
	convert the files found

***************************************/

static Word BURGER_API WildCard(const char *pDirectory,const char *pWildcard,eTextType eType,Word bRecursive)
{
	Word bChanged = FALSE;
	DirectorySearch MyDir;
	if (!MyDir.Open(pDirectory)) {				// Open the directory
		while (!MyDir.GetNextEntry()) {			// Get the first file
			if (!MyDir.m_bHidden && !MyDir.m_bLocked) {
				if (!MyDir.m_bDir) {
					// Matched the wildcard?
					if (!Wildcardcmp(MyDir.m_Name,pWildcard)) {
						bChanged = TRUE;
						Filename Work(pDirectory);
						Work.Append(MyDir.m_Name);
						bChanged |= AddLF(&Work,&Work,eType);
						//								Globals::SetErrorCode(10);
					}
				} else if (bRecursive) {
					String NewDir(pDirectory,MyDir.m_Name,":");
					bChanged |= WildCard(NewDir.GetPtr(),pWildcard,eType,bRecursive);
				}
			}
		}
		MyDir.Close();
	}
	return bChanged;
}

/***************************************

	Simple utility to add linefeeds to a Macintosh
	or Apple II type text file for use on Messy DOS machines

***************************************/

int BURGER_ANSIAPI main(int argc,const char **argv)
{
	ConsoleApp MyApp(argc,argv);

	// Switches

	CommandParameterBooleanTrue MacOS("Convert to MacOS format","m");
	CommandParameterBooleanTrue Windows("Convert to Windows format","w");
	CommandParameterBooleanTrue Linux("Convert to Linux format","l");
	CommandParameterBooleanTrue Recurse("Recurse through all subdirectories","r");

	const CommandParameter *MyParms[] = {
		&MacOS,
		&Windows,
		&Linux,
		&Recurse
	};
	argv = MyApp.GetArgv();
	argc = CommandParameter::Process(MyApp.GetArgc(),argv,MyParms,sizeof(MyParms)/sizeof(MyParms[0]),
		"Usage: addlf InputFile [Outputfile]\n\n"
		"This will convert any text file into a specific format.\n"
#if defined(BURGER_WINDOWS) || defined(BURGER_MSDOS)
		"The default is Windows format. "
#elif defined(BURGER_MAC)
		"The default is MacOS format. "
#else
		"The default is Linux format. "
#endif
		"Copyright Rebecca Ann Heineman.\n",2,3);
	Globals::SetErrorCode(10);
	if (argc>=0) {
		MyApp.SetArgc(argc);

		// Set the type of text file output
		eTextType eType;
#if defined(BURGER_WINDOWS) || defined(BURGER_MSDOS)
		eType = TEXTTYPE_WINDOWS;
#elif defined(BURGER_MAC)
		eType = TEXTTYPE_MACOS;
#else
		eType = TEXTTYPE_LINUX;
#endif
		// Switch for the text file type
		if (MacOS.GetValue()) {
			eType = TEXTTYPE_MACOS;
		}
		if (Linux.GetValue()) {
			eType = TEXTTYPE_LINUX;
		}
		if (Windows.GetValue()) {
			eType = TEXTTYPE_WINDOWS;
		}

		Filename InputFilename;
		InputFilename.SetFromNative(argv[1]);
		Word bChanged = FALSE;
		if (argc!=2) {
			if (HasWildcard(InputFilename.GetPtr())) {
				printf("Wild cards not allowed in two parameter commands.\n");
				Globals::SetErrorCode(10);
			} else {
				Filename OutputFilename;
				OutputFilename.SetFromNative(argv[2]);
				bChanged = AddLF(&InputFilename,&OutputFilename,eType);
			}
		} else {
			Word bRecurse = Recurse.GetValue();
			if (HasWildcard(InputFilename.GetPtr())) {
				bChanged = WildCard("8:",argv[1],eType,bRecurse);
			} else {
				bChanged = AddLF(&InputFilename,&InputFilename,eType);
			}
		}
	}
	return Globals::GetErrorCode();
}
