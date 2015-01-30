/***************************************

	HydroCarbon post linker
	
	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com
 
	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!
	
***************************************/

#define CWPLUGIN_LONG_FILENAME_SUPPORT 0
#include <burger.h>
#include <CodeFragments.h>
#include <Resources.h>
#include <string.h>
#include "CWPlugins.h"
#include "CWPluginErrors.h"
#include "DropInCompilerLinker.h"

#define CODEMASK 0x03
#define CODECARBON 0x01
#define CODEALTIVEC 0x02
#define CODEPOWERPC 0x80

static const char Before1[] = "FetDiskFragment";	/* Misspelled GetDiskFragment */
static const char Before2[] = "FloseConnection";	/* Misspelled CloseConnection */
static const char AltivecName[] = "altivec";

static const Word8 PhonyCFrag[0x38] = {
	0x70,0x77,0x70,0x63,		/* 'pwpc' */
	0x00,0x00,					/* reservedA */
	0x00,						/* reservedB */
	0x00,						/* updateLevel */
	0x00,0x00,0x00,0x00,		/* currentVersion */
	0x00,0x00,0x00,0x00,		/* oldDefVersion */
	0x00,0x00,0x00,0x00,		/* uUsage1 (Stacksize) (Patch) */
	0x00,0x00,					/* uUsage2 (reserved) */
	0x01,						/* usage */
	0x01,						/* where */
	0x00,0x00,0x00,0x00,		/* offset (Patch) */
	0x00,0x00,0x00,0x00,		/* length (Patch) */
	0x00,0x00,0x00,0x00,		/* uWhere1 */
	0x00,0x00,					/* uWhere2 */
	0x00,0x00,					/* extensionCount */
	0x00,0x38,					/* memberSize */
	0x0B,'H','y','d','r','o','C','a','r','b','o','n'
};

/***************************************

	Perform a strstr() but case insensitive

***************************************/

static char * stristr2(const char *Input, const char *SubStr)
{
	Word Temp;
	Temp = ((Word8 *)Input)[0];		/* Get the first character */
	if (Temp) {						/* Do I even bother? */
		do {
			Word i;
			Word Temp2;
			i = 0;					/* Init the index */
			do {
				Temp2 = ((Word8 *)SubStr)[i];	/* Get the first char of the test string */
				if (!Temp2) {					/* Match? */
					return (char *)Input;		/* I matched here! */
				}
				Temp = ((Word8 *)Input)[i];		/* Get the source string */
				++i;							/* Ack the char */
				if (Temp2>='A' && Temp2<='Z') {	/* Convert to lower case */
					Temp2 += 32;
				}
				if (Temp>='A' && Temp<='Z') {	/* Convert to lower case */
					Temp += 32;
				}
			} while (Temp == Temp2);			/* Match? */
			++Input;							/* Next main string char */
			Temp = ((Word8 *)Input)[0];			/* Next entry */
		} while (Temp);							/* Source string still ok? */
	}
	return 0;		/* No string match */
}

/***************************************

	Convert a Pascal string into a "C" string.
	Since I get the length byte immediately, I can do a fast
	Word32 copy to move the bulk of the string.

***************************************/

static void PStr2CStr2(char *DestPtr,const char *SrcPtr)
{
	Word Temp1,Temp2;

	Temp1 = ((Word8 *)SrcPtr)[0];	/* Get the string length */
	SrcPtr++;
	Temp2 = Temp1>>2;			/* Get the longword count */
	if (Temp2) {		/* Any longwords? */
		do {
			Word32 Temp;
			Temp = ((Word32 *)SrcPtr)[0];
			SrcPtr+=4;
			((Word32 *)DestPtr)[0] = Temp;	/* Copy a byte */
			DestPtr+=4;
		} while (--Temp2);	/* Count down */
	}
	Temp1 = Temp1&3;		/* Any bytes left? */
	if (Temp1) {
		do {
			DestPtr[0] = SrcPtr[0];		/* Copy a byte */
			++SrcPtr;
			++DestPtr;
		} while (--Temp1);	/* Count down */
	}
	DestPtr[0] = 0;		/* Terminating zero */
}

/***************************************

	GIven an open resource file, check if it is
	a carbon app.
	
	The test is simple, check for a cfrg(0) resource
	to rule out 680x0 code and then check for a carb
	resource for the carbon flag
	If both are true, then it's a Carbon app
	
	This is really only for a sanity check. The data isn't used for the output
	
***************************************/

static int DetermineType(void)
{
	Handle CfrgResource;
	CFragResource *RezPtr;
	CFragResourceMember *MemberPtr;
	int Count;
	int PowerPCFlag;
	
	/* Assume an unknown file */
	
	PowerPCFlag = 0;		/* Assume bogus */
	
	CfrgResource = Get1Resource(kCFragResourceType,0);	/* Get the cfrg resource */
	
	if (CfrgResource) {		/* Found a CFM fragment */
//		HLock(CfrgResource);		/* Lock it down */

		RezPtr = (CFragResource *)(CfrgResource[0]);		/* Deref the handle */
		Count = RezPtr->memberCount;						/* How many fragments exist? */
		if (Count) {
			MemberPtr = &RezPtr->firstMember;				/* Go to the first entry */
			do {
				/* Power PC fragment? */
				/* Must be PowerPC, data fork and an app fragment */
				/* Otherwise, I'll ignore it */
				
				if ((MemberPtr->architecture==kPowerPCCFragArch) &&
					(MemberPtr->usage == kApplicationCFrag) &&
					(MemberPtr->where == kDataForkCFragLocator)) {
					PowerPCFlag = CODEPOWERPC;			/* Looks good */
					if (Count1Resources('carb')) {		/* Is this the carbon app? */
						PowerPCFlag |= CODECARBON;	/* This file says it's carbon! */
					}
					break;
				}
				MemberPtr = (CFragResourceMember *)(((Word8 *)MemberPtr)+MemberPtr->memberSize);
			} while (--Count);
		}
//		HUnlock(CfrgResource);		/* Release the handle */
	}
	return PowerPCFlag;				/* Return if PowerPC/Carbon */
}

/***************************************

	Given a file image of the data to the magic loader,
	patch it so it can do it's dirty work.
	
	Why patch you ask?
	
	You see, to perform the magic, the code fragment needs to
	be able to link to two seperate libraries using the same
	function names. You cannot use the linker since the linker will
	match the first library and never use a second one.
	
	So, I intentionally linked to a mispelling of the functions. I need to
	correct the spelling for this to function.
	Then I need to patch 4 longword having the offset and lengths
	of the carbon and classic data images
	
	Note : Set Found to 3 to NOT patch the filenames
	
***************************************/

static short PatchMagic(CWPluginContext context,unsigned int Found,char *Magic,long MagicSize,long *SizeArray)
{
	long TempLength15;
	long TempLength4;
	long i;
	
	TempLength15 = MagicSize-15;
	if (TempLength15<=0) {
		CWReportMessage(context, 0, "HydroCarbon : Loader is damaged or missing",0,messagetypeError,0);
		return cwErrInvalidParameter;
	}
	TempLength4 = MagicSize-4;
	
	/* This mess is to scan the data once */
	
	i = 0;
	do {
	
		/* Try to patch "FetDiskFragment" */
	
		if (!(Found&0x01) && (i<TempLength15)) {
			if (!memcmp(Before1,Magic,15)) {
				Magic[0] = 'G';
				Found |= 0x01;
			}
		}

		/* Try to patch "FloseConnection" */
		
		if (!(Found&0x02) && (i<TempLength15)) {
			if (!memcmp(Before2,Magic,15)) {
				Magic[0] = 'C';
				Found |= 0x02;
			}
		}

		/* Patch the size arrays */
		
		if (!(Found&0x04)) {
			if (((long *)Magic)[0] == 0xD5AA9601) {
				((long *)Magic)[0] = SizeArray[0];
				Found |= 0x04;
			}
		}

		if (!(Found&0x08)) {
			if (((long *)Magic)[0] == 0xD5AA9602) {
				((long *)Magic)[0] = SizeArray[1];
				Found |= 0x08;
			}
		}

		if (!(Found&0x10)) {
			if (((long *)Magic)[0] == 0xD5AA9603) {
				((long *)Magic)[0] = SizeArray[2];
				Found |= 0x10;
			}
		}

		if (!(Found&0x20)) {
			if (((long *)Magic)[0] == 0xD5AA9604) {
				((long *)Magic)[0] = SizeArray[3];
				Found |= 0x20;
			}
		}
		++Magic;
	} while (++i<TempLength4);
	
	if (Found!=0x3F) {
		CWReportMessage(context, 0, "HydroCarbon : Loader could not be patched",0,messagetypeError,0);
		return cwErrInvalidParameter;
	}
	return cwNoErr;			/* No error */
}

/***************************************

	Happy fun merge code
	Read in the cfrg resource and insert the new entry
	in it.
	
	Also as I am scanning, get the offsets to the Classic
	and the Carbon images and place them in the loader table
	
***************************************/

static short PerformMerge(CWPluginContext context,long FileLength,long MagicLength,long *SizeArray)
{
	Handle CfrgResource;
	CFragResource *RezPtr;
	CFragResourceMember *MemberPtr;
	int Count;
	long FragSize;
	long Stack;
	
	/* Init the size array, (I'm paranoid) */
	
	SizeArray[0] = 0;
	SizeArray[1] = 0;
	SizeArray[2] = 0;
	SizeArray[3] = 0;
	
	/* Assume an unknown file */
		
	CfrgResource = Get1Resource(kCFragResourceType,0);		/* Get the cfrg resource from the final file */
	
	if (!CfrgResource) {		/* Found a CFM fragment */
		CWReportMessage(context, 0, "HydroCarbon : Cannot open output cfrg resource",0,messagetypeError,0);
		return cwErrOSError;
	}

	FragSize = GetHandleSize(CfrgResource)+0x38;
	HUnlock(CfrgResource);
	SetHandleSize(CfrgResource,FragSize);		/* Add space for my record */
	
	HLock(CfrgResource);						/* Lock it down */

	/* Now, scan the code fragments and change the app */
	/* fragments into shared library fragments */
	
	RezPtr = (CFragResource *)(CfrgResource[0]);		/* Deref the handle */
	Count = RezPtr->memberCount;						/* How many fragments exist? */
	Stack = 0;
	if (Count) {
		int index;
		MemberPtr = &RezPtr->firstMember;				/* Go to the first entry */
		index = 0;			/* For storing the offsets */
		do {
			/* Power PC fragment? */
			/* Must be PowerPC, data fork and an app fragment */
			/* Otherwise, I'll ignore it */
			
			if ((MemberPtr->architecture==kPowerPCCFragArch) &&
				(MemberPtr->usage == kApplicationCFrag) &&
				(MemberPtr->where == kDataForkCFragLocator)) {
				MemberPtr->usage = kImportLibraryCFrag;
				if (Stack<MemberPtr->uUsage1.appStackSize) {		/* Use the larger stack */
					Stack = MemberPtr->uUsage1.appStackSize;		/* Get the stack size */
				}
				if (index<4) {			/* Failsafe */
					SizeArray[index] = MemberPtr->offset;			/* Store the offset */
					SizeArray[index+1] = MemberPtr->length;
					index+=2;
				}
			}
			MemberPtr = (CFragResourceMember *)(((Word8 *)MemberPtr)+MemberPtr->memberSize);
		} while (--Count);
		if (index>=4) {			/* Failsafe */
			MemberPtr = &RezPtr->firstMember;				/* Go to the first entry */
			BlockMove(MemberPtr,(char *)MemberPtr+0x38,FragSize-(0x38+0x20));
			BlockMove(PhonyCFrag,MemberPtr,0x38);
			RezPtr->memberCount++;
			MemberPtr->uUsage1.appStackSize = Stack;
			MemberPtr->offset = FileLength;
			MemberPtr->length = MagicLength;

//			HUnlock(CfrgResource);		/* Release the handle */
			ChangedResource(CfrgResource);		/* Tell the resource manager to write the resource */
			return cwNoErr;			/* True if PowerPC */
		}
	}
	CWReportMessage(context, 0, "HydroCarbon : Could not find 2 PowerPC app fragments in output",0,messagetypeError,0);
	return cwErrOSError;
}

/***************************************

	Insert a module
	
***************************************/

static int InsertAModule(CWPluginContext context,CWTargetInfo *TargetInfo,int ModuleNumber)
{
	Handle MagicData;
	long MagicDataSize;
	long FileLength;
	Ptr MagicDataPtr;
	long WriteCount;
	long SizeArray[4];		/* Classic Offset/Length, Carbon Offset/Length */
	short FileDataRef;
	short FileResRef;
	CWResult err;

	/* Now, let's prepare my Code Fragment */
	
	MagicData = Get1Resource('HYDR',ModuleNumber);
	if (!MagicData) {
		CWReportMessage(context, 0, "HydroCarbon : Cannot find magic loader", 0, messagetypeError, 0);
		return cwErrOSError;
	}
	MagicDataSize = GetHandleSize(MagicData);
	HLock(MagicData);
	MagicDataPtr = MagicData[0];
	
	/* Let's open the output data file. */
	/* I need to do it now so that I can get the offset to the file */
	/* where I will insert the magic code */
	
	if (FSpOpenDF(&TargetInfo->outfile,fsRdWrPerm,&FileDataRef)) {
		HUnlock(MagicData);			/* Oh hell */
		ReleaseResource(MagicData);
		CWReportMessage(context, 0, "HydroCarbon : Error in opening output data fork", 0, messagetypeError, 0);
		return cwErrOSError;
	}
	
	GetEOF(FileDataRef,&FileLength);	/* Length of the file */
	FileLength=(FileLength+15)&(~15);		/* Round up */
	SetEOF(FileDataRef,FileLength);		/* Set the EOF */
	SetFPos(FileDataRef,fsFromStart,FileLength);	/* Set the file mark so I can write the magic data */

	/* Now, let's get the cfrg resource and get the data inside */
	/* I will also insert the magic data into the cfrg */
	
	FileResRef = FSpOpenResFile(&TargetInfo->outfile,fsRdWrPerm);
	if (FileResRef==-1) {
		FSClose(FileDataRef);
		CWReportMessage(context, 0, "HydroCarbon : Error in opening output resource", 0, messagetypeError, 0);
		return cwErrOSError;
	}
	PerformMerge(context,FileLength,MagicDataSize,SizeArray);
	UpdateResFile(FileResRef);
	CloseResFile(FileResRef);

	/* Need the code fragement to get the size, this is important! */
	
	if (ModuleNumber) {		/* Zero, passes a zero, otherwise, I pass a 3 */
		ModuleNumber = 3;
	}
	err = PatchMagic(context,ModuleNumber,MagicDataPtr,MagicDataSize,SizeArray);
	if (err!=cwNoErr) {
		HUnlock(MagicData);
		ReleaseResource(MagicData);
		return err;
	}
	
	WriteCount = MagicDataSize;
	FSWrite(FileDataRef,&WriteCount,MagicDataPtr);
	FSClose(FileDataRef);
	
	/* At this point, I don't need the magic data */
	
	HUnlock(MagicData);
	ReleaseResource(MagicData);
	return err;
}


/***************************************

	Main entry point for the post-linker
	
***************************************/

static CWResult	InsertHydrocarbon(CWPluginContext context)
{
	char WorkFilename[256];
	char TextMsg[512];
	long index;
	CWResult err;
	long filecount;
	unsigned short FinderFlags;
	CWTargetInfo TargetInfo;
	FInfo FooInfo;
	CWProjectFileInfo fileInfo;
	short FileResRef;
	int PowerPCFlag;
	
	Word32 TypeArray;		/* Bit field for data found */
								
	/* Process all the files in my project */
	/* I should have a maximum of 4 files that contain PPC */
	/* object code. Of them, one pair should be carbon, the other */
	/* pair classic. */
	/* All other files are ignored since they contain resources */
	/* 680x0 code or other data that I could care less about */
	
	err = CWGetProjectFileCount(context, &filecount);
	if (err != cwNoErr)	{
		return err;
	}
	
	if (!filecount) {
		CWReportMessage(context, 0, "HydroCarbon : No input files are present",0,messagetypeError,0);
		return cwErrInvalidParameter;
	}
	
	index = 0;
	FinderFlags = 0;
	TypeArray = 0;
		
	/* Scan all the input file and glean from this whether */
	/* I am making a valid file */
	/* Determine what types of files I have (Classic/Carbon/Altivec) */
	
	do {
		/* first, get info about the current file */
		
		err = CWGetFileInfo(context,index,FALSE,&fileInfo);
		if (err != cwNoErr) {
			return err;			/* Surrender Dorothy! */
		}

		FileResRef = FSpOpenResFile(&fileInfo.filespec,fsRdPerm);
		if (FileResRef==-1) {
			return cwErrOSError;
		}
		PowerPCFlag = DetermineType();		/* PPC? Carbon? */
		CloseResFile(FileResRef);

		if (PowerPCFlag&CODEPOWERPC) {		/* Is this PowerPC? (I skip 680x0 files) */
		
			/* Look at the filename for the word "Altivec" */
			
			PStr2CStr2(WorkFilename,(char *)fileInfo.filespec.name);
			if (stristr2(WorkFilename,AltivecName)) {		/* Does the name contain "altivec"? */
				PowerPCFlag |= CODEALTIVEC;					/* I'll assume this is altivec */
			}
			
			/* Now, have I already processed such a file? */
			
			if (TypeArray & (1<<(PowerPCFlag&CODEMASK))) {
				const char *FooMsg;
				strcpy(TextMsg,"HydroCarbon : Only 1 ");
				switch (PowerPCFlag&CODEMASK) {
				case 0:
					FooMsg = "Classic";
					break;
				case CODECARBON:
					FooMsg = "Carbon";
					break;
				case CODEALTIVEC:
					FooMsg = "Altivec/Classic";
					break;
				default:
					FooMsg = "Altivec/Carbon";
					break;
				}
				strcat(TextMsg,FooMsg);
				strcat(TextMsg," application is allowed");
				CWReportMessage(context, 0, TextMsg, 0, messagetypeError, 0);
				return cwErrInvalidParameter;		/* As good as error as any! */
			}
			
			/* Mark as found */
			
			TypeArray |= 1<<(PowerPCFlag&CODEMASK);
			
			if (PowerPCFlag&CODECARBON) {
				/* Note to self... This is important!! */
				/* Use the finder flags from the CARBON apps! */
				
				if (!FinderFlags) {
					if (FSpGetFInfo(&fileInfo.filespec,&FooInfo)) {
						return cwErrOSError;
					}
					FinderFlags = FooInfo.fdFlags;
				}
			}
		}	
	} while (++index<filecount);

	/* Ok, Let's give the user the third degree, in the form of sanity checks! */
	
	/* Anything found? */
	
	if (!TypeArray) {		
		CWReportMessage(context, 0, "HydroCarbon : No PowerPC input files found", 0, messagetypeError, 0);
		return cwErrInvalidParameter;		/* As good as error as any! */
	}

	/* I only have 5 combinations I support, give an */
	/* error message that makes sense on all the others */
	
	if (TypeArray!=15 && TypeArray!=3 && TypeArray!=5 &&
		TypeArray!=0xC && TypeArray!=0xA) {	/* The works? */
		const char *ErrFooPtr;
		if (TypeArray==1) {						/* Is there a classic app? */
			ErrFooPtr = "HydroCarbon : No Carbon or Altivec Classic input file found";
		} else if (TypeArray==2) {
			ErrFooPtr = "HydroCarbon : No Classic or Altivec Carbon input file found";
		} else if (TypeArray==4) {
			ErrFooPtr = "HydroCarbon : No Classic or Altivec Carbon input file found";
		} else if (TypeArray==8) {
			ErrFooPtr = "HydroCarbon : No Carbon or Altivec Classic input file found";
		} else if (TypeArray==6 || TypeArray==0xE) {
			ErrFooPtr = "HydroCarbon : No Classic input file found";
		} else if (TypeArray==7) {
			ErrFooPtr = "HydroCarbon : No Altivec Carbon input file found";
		} else if (TypeArray==0xB) {
			ErrFooPtr = "HydroCarbon : No Altivec Classic input file found";
		} else {
		//if (TypeArray==9 || TypeArray==0xD)
			ErrFooPtr = "HydroCarbon : No Carbon input file found";
		}
		CWReportMessage(context, 0, ErrFooPtr, 0, messagetypeError, 0);
		return cwErrInvalidParameter;		/* As good as error as any! */
	}
	
	/* Ok, we have1 of the 5 combinations */
	/* so far, so good. */
	/* Now, let's do the dirty deed and merge the suckers!!! */
	
	err = CWGetTargetInfo(context,&TargetInfo);
	if (err!=cwNoErr) {
		return err;
	}

	/* Huh??!?!? */
	
	if (TargetInfo.outputType != linkOutputFile) {
		return cwErrRequestFailed;
	}

	/* Easy stuff, let's move the flags from the carbon app */
	/* to my output file */
	
	if (TypeArray&0x0A) {		/* Carbon? */
		if (FSpGetFInfo(&TargetInfo.outfile,&FooInfo)) {
			return cwErrOSError;
		}
		FooInfo.fdFlags = FinderFlags;
		if (FSpSetFInfo(&TargetInfo.outfile,&FooInfo)) {
			return cwErrOSError;
		}
	}
	
	/* Standard Classic/Carbon combination */
	
	if (TypeArray==3 || TypeArray==0xC) {
		return InsertAModule(context,&TargetInfo,0);		/* Classic/Carbon */
	}
	
	/* Carbon only */
	
	if (TypeArray==0xA) {
		return InsertAModule(context,&TargetInfo,1);		/* Altivec Carbon */
	}		

	/* Classic only */
	
	if (TypeArray==0x5) {
		return InsertAModule(context,&TargetInfo,2);		/* Altivec Classic */
	}		

	err = cwErrInvalidParameter;
	return err;
}
	

/***************************************

	Main entry point for the post-linker
	
***************************************/

pascal short main(CWPluginContext context)
{
	short result;
	long request;

	/* First, what type of command shall I process? */
	
	if (CWGetPluginRequest(context, &request) != cwNoErr) {
		return cwErrRequestFailed;		/* Yeah right... */
	}

	result = cwNoErr;

	/* dispatch on linker request */
	switch (request) {
	default:
		result = cwErrRequestFailed;
		break;

	case reqLink:			/* build the final executable */
		result = InsertHydrocarbon(context);

	case reqInitLinker:		/* linker has just been loaded into memory */
//		break;

	case reqTermLinker:		/* linker is about to be unloaded from memory */
//		break;

	case reqDisassemble:	/* Disassemble the data */
//		break;

	case reqTargetInfo:		/* Return info about the target if a control panel changed */
		break;
	}
	
	/* Send the result back */
	return CWDonePluginRequest(context, result);		/* Pass back the result code */
}
