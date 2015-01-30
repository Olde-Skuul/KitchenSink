/***************************************

	Tool to invoke CodeWarrior's IDE for
	automatic building and project management
	
	Note: This uses Carbon libraries that are not
	available in 64 bit CPUs, so only compile
	for 32 bit CPUs

	Inspired by a tool of the same name by Josef W. Wankerl
	of Metrowerks Corporation
	
	Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

	It is released under an MIT Open Source license. Please see LICENSE
	for license details. Yes, you can use it in a
	commercial title without paying anything, just give me a credit.
	Please? It's not like I'm asking you for money!

***************************************/

// Burger::Palette collides with Palette in Carbon.h (OSX)
#define BURGER_NO_USING_NAMESPACE
#include <burger.h>
#include <stdlib.h>
#if defined(BURGER_MACOSX)
#include <Carbon/Carbon.h>
#else
#include <Files.h>
#include <AEDataModel.h>
#include <AEInteraction.h>
#include <Processes.h>
#include <LaunchServices.h>
#include <StringCompare.h>
#endif
using namespace Burger;

static const Word8 g_BooleanTrue = TRUE;
static const Word32 g_NoYes[2] = {'no  ','yes '};
static const char g_Version[] = "2.0";
static const char g_BuildNumber[] = "Build 103";
static const char g_AppName[] = "cmdide";

/***************************************

	Obtain all the error messages and send them over to an open file

***************************************/

static void PrintErrorsOrWarnings(const AEDesc *pErrorList,Word bWarnings,FILE *fp)
{
	long mItemCount;
	if (!AECountItems(pErrorList,&mItemCount)) {
		long lItemCount = mItemCount;
		if (lItemCount) {
			long lIndex=1;
			do {
				// Obtain the error message from the Apple Event list
				AEKeyword MyKeyWord;
				AEDesc AEResult;
				if (AEGetNthDesc(pErrorList,lIndex,'ErrM',&MyKeyWord,&AEResult)) {
					break;
				}
				// Get the error type
				Size lActualSize;
				DescType MyDescType;
				Word32 eErrorType;
				if (!AEGetParamPtr(&AEResult,'ErrT','enum',&MyDescType,&eErrorType,sizeof(eErrorType),&lActualSize)) {
					// Determine if it's a warning or an error. Skip if neither.
					Word bValid = FALSE;
					if (bWarnings) {
						if ((eErrorType=='ErCW') || (eErrorType=='ErLW')) {
							bValid = TRUE;
						}
					} else if ((eErrorType=='ErCE') || (eErrorType=='ErLE') || (eErrorType=='ErGn')) {
						bValid = TRUE;
					}

					// It's something of interest, print it.
					if (bValid) {
						// Get the error message
						char TextBuffer[1024];
						if (!AEGetParamPtr(&AEResult,'ErrS','TEXT',&MyDescType,&TextBuffer,sizeof(TextBuffer)-1,&lActualSize)) {
							// Force to a "C" string
							TextBuffer[lActualSize] = 0;
							if (bWarnings) {
								fprintf(fp,"Warning : %s\n",TextBuffer);
							} else {
								fprintf(fp,"Error   : %s\n",TextBuffer);
							}
							// Print the file and line number (If applicable)
							bValid = FALSE;
							FSSpec MyFileSpec;
							if (!AEGetParamPtr(&AEResult,'file','fss ',&MyDescType,&MyFileSpec,sizeof(MyFileSpec),&lActualSize)) {
								bValid = TRUE;
								// Print the filename
								MyFileSpec.name[MyFileSpec.name[0]+1] = 0;
								fprintf(fp,"%s",(char *)(&MyFileSpec.name[1]));
							}
							// Obtain the line number
							long lLineNumber;
							if (!AEGetParamPtr(&AEResult,'ErrL','long',&MyDescType,&lLineNumber,sizeof(lLineNumber),&lActualSize)) {
								bValid = TRUE;
								// Print the line number
								fprintf(fp,"line %ld",lLineNumber);
							}
							// Add a CR if a filename or line number was printed
							if (bValid) {
								fprintf(fp,"\n");
							}
						}
					}
				}
				// Clean up
				AEDisposeDesc(&AEResult);
			} while (++lIndex<=lItemCount);
		}
	}
}

/***************************************

	Return TRUE if there are any items in the AEDesc structure

***************************************/

static Word IsThereAnyItems(const AEDesc *pAEDesc)
{
	long mItemCount;
	Word bResult;
	// Get the count. Fail on error or a count less than 1
	if (!AECountItems(pAEDesc,&mItemCount) && (mItemCount>0)) {
		bResult = TRUE;
	} else {
		bResult = FALSE;
	}
	return bResult;
}

/***************************************

	Scan active processes until the CodeWarrior IDE is found

***************************************/

static int IsCodeWarriorRunning(const char *pIDEName,ProcessSerialNumber *pProcess)
{
	// Initialize the process ID to zero, so the scanning begins with
	// the first process
	
	pProcess->highLongOfPSN = 0;
	pProcess->lowLongOfPSN = 0;

	// Initialize the ProcessInfoRef
	ProcessInfoRec MyProcessInfo;
	// Set the structure size
	MyProcessInfo.processInfoLength = sizeof(ProcessInfoRec);
	// I'm not interested in the process' name
	MyProcessInfo.processName = NULL;

	int iError;
	
	// If there is no supplied name, just find the first app with the CodeWarrior signature
	
	if (!pIDEName) {
		// I'm not interested in the FSSpec
		MyProcessInfo.processAppSpec = NULL;
		
		// Scan for the signature CWIE. If found,
		// iResult will be zero, otherwise, it's an error code
		do {
			// Start scanning from here
			iError = GetNextProcess(pProcess);
			if (iError) {
				break;
			}
			iError = GetProcessInformation(pProcess,&MyProcessInfo);
			if (iError) {
				break;
			}
		} while (MyProcessInfo.processSignature!='CWIE');
	} else {
	
		// Since I have a name, see if it's available specifically
		// This is the preferred method, since the user could have multiple
		// versions of Codewarrior installed
		
		Boolean bDirectory;
		FSRef MyRef;
		
		// First, take the filename and convert to an FSSpec so I can scan for a match
		iError = FSPathMakeRef(reinterpret_cast<const UInt8 *>(pIDEName),&MyRef,&bDirectory);
		if (!iError) {
			FSSpec MySpec;
			// Convert to an FSSpec
			iError = FSGetCatalogInfo(&MyRef,kFSCatInfoNone,NULL,NULL,&MySpec,NULL);
			if (!iError) {
				// I want the FSSpec of the processes being scanned
				FSSpec ProcessSpec;
				MyProcessInfo.processAppSpec = &ProcessSpec;
				do {	
					iError = GetNextProcess(pProcess);
					if (iError) {
						break;
					}
					iError = GetProcessInformation(pProcess,&MyProcessInfo);
					if (iError) {
						break;
					}
				// Break if we have a match!
				} while ((MyProcessInfo.processSignature!='CWIE') ||
					(MySpec.vRefNum != ProcessSpec.vRefNum) ||
					(MySpec.parID!=ProcessSpec.parID) || 
					(MySpec.name[0] != ProcessSpec.name[0]) ||
					MemoryCompare(&MySpec.name[1],&ProcessSpec.name[1],MySpec.name[0]));
			}
		}
	}
	return iError;
}

/***************************************

	Open the IDE and return the process ID
	Return 0 if the IDE was found and is runnings

***************************************/

static int FindOrLaunchCodeWarrior(const char *pIDEName,ProcessSerialNumber *pProcess)
{
	// Is it already running?
	int iResult = IsCodeWarriorRunning(pIDEName,pProcess);
	if (iResult) {
		// It's not running yet. Launch it!
		FSRef MyRef;
		// Do I have a name?
		if (!pIDEName) {
			// Launch the default app that has the "CWIE" ID
			iResult = LSGetApplicationForInfo(kLSUnknownType,'CWIE',NULL,kLSRolesAll,&MyRef,NULL);
		} else {
			// Launch from a specific pathname
			Boolean bDirectory;
			iResult = FSPathMakeRef(reinterpret_cast<const UInt8 *>(pIDEName),&MyRef,&bDirectory);
		}
		// Did I find the file reference?
		if (!iResult) {
			// Start up the application!
			iResult = LSOpenFSRef(&MyRef,NULL);
			if (!iResult) {
				// Wait until the app has started
				do {
					iResult = IsCodeWarriorRunning(pIDEName,pProcess);
				} while (iResult);
			}
		}
	}
	return iResult;
}

/***************************************

	Create an Apple Event targeting the CodeWarrior IDE

***************************************/

static int CreateAppleEventForCodeWarrior(AEDesc *pDesc,Word32 uEventClass,Word32 uEventID,const char *pIDEName)
{
	ProcessSerialNumber MyProcessNumber;
	// Launch codewarrior
	int iResult = FindOrLaunchCodeWarrior(pIDEName,&MyProcessNumber);
	if (!iResult) {
		// Nameless app?
		AEDesc MyDesc;
		if (!pIDEName) {
			// Send to the generic ID
			Word32 uSignature = 'CWIE';
			iResult = AECreateDesc(typeApplSignature,&uSignature,sizeof(uSignature),&MyDesc);
		} else {
			// Send to the specific ID
			iResult = AECreateDesc(typeProcessSerialNumber,&MyProcessNumber,sizeof(MyProcessNumber),&MyDesc);
		}
		// No problem making the event?
		if (!iResult) {
			// Let's send the event to CodeWarrior
			iResult = AECreateAppleEvent(uEventClass,uEventID,&MyDesc,kAutoGenerateReturnID,kAnyTransactionID,pDesc);
			AEDisposeDesc(&MyDesc);
		}
	}
	return iResult;
}

/***************************************

	Instruct CodeWarrior to build the project and return the error list

***************************************/

static int BuildTarget(AEDesc *pDesc,const char *pIDEName)
{
	AEDesc BuildEvent;
	// Create the Build event
	int iError = CreateAppleEventForCodeWarrior(&BuildEvent,'MMPR','Make',pIDEName);
	if (!iError) {
		// Add the message parameter 'Errs' = TRUE to get the error list
		iError = AEPutParamPtr(&BuildEvent,'Errs','bool',&g_BooleanTrue,sizeof(g_BooleanTrue));
		if (!iError) {
			AEDesc MyReply;
			AEInitializeDesc(&MyReply);
			// Tell CodeWarrior to build the project
			iError = AESend(&BuildEvent,&MyReply,kAEDontRecord+kAECanInteract+kAEQueueReply+kAENoReply,kAENormalPriority,kNoTimeOut,NULL,NULL);
			if (!iError) {
				// Get the error list, if any
				iError = AEGetParamDesc(&MyReply,'----','list',pDesc);
				AEDisposeDesc(&MyReply);
			}
		}
		AEDisposeDesc(&BuildEvent);
	}
	return iError;
}

/***************************************

	Tell CodeWarrior to close a project
	Return zero on success

***************************************/

static int CloseProject(const char *pIDEName,int iTimeout)
{
	AEDesc CloseEvent;
	// Create a "Close Project File" event
	int iError = CreateAppleEventForCodeWarrior(&CloseEvent,'MMPR','ClsP',pIDEName);
	if (!iError) {
		AEDesc MyReply;
		AEInitializeDesc(&MyReply);
		iError = AESend(&CloseEvent,&MyReply,kAEDontRecord+kAECanInteract+kAEQueueReply+kAENoReply,kAENormalPriority,iTimeout,NULL,NULL);
		if (!iError) {
			AEDisposeDesc(&MyReply);
		}
		AEDisposeDesc(&CloseEvent);
	}
	return iError;
}

/***************************************

	Tell CodeWarrior to shut down
	Return zero on success

***************************************/

static int ShutDownCodeWarrior(const char *pIDEName,int iTimeOut)
{
	AEDesc QuitEvent;
	// Create an OS Generic "Quit Application" event
	int iError = CreateAppleEventForCodeWarrior(&QuitEvent,'aevt','quit',pIDEName);
	if (!iError) {
		AEDesc MyReply;
		AEInitializeDesc(&MyReply);
		iError = AESend(&QuitEvent,&MyReply,kAEDontRecord+kAECanInteract+kAEQueueReply+kAENoReply,kAENormalPriority,iTimeOut,NULL,NULL);
		if (!iError) {
			AEDisposeDesc(&MyReply);
		}
		AEDisposeDesc(&QuitEvent);
	}
	return iError;
}

/***************************************

	Tell CodeWarrior to remove all the binaries
	Return zero on success

***************************************/

static int CleanProject(const char *pIDEName,int iTimeOut)
{
	AEDesc CleanEvent;
	// Create a "Remove Binaries" event
	int iError = CreateAppleEventForCodeWarrior(&CleanEvent,'MMPR','RemB',pIDEName);
	if (!iError) {
		AEDesc MyReply;
		AEInitializeDesc(&MyReply);
		iError = AESend(&CleanEvent,&MyReply,kAEDontRecord+kAECanInteract+kAEQueueReply+kAENoReply,kAENormalPriority,iTimeOut,NULL,NULL);
		if (!iError) {
			AEDisposeDesc(&MyReply);
		}
		AEDisposeDesc(&CleanEvent);
	}
	return iError;
}

/***************************************

	Tell CodeWarrior to set the active project
	Return zero on success

***************************************/

static int SetBuildTarget(const char *pTargetName,const char *pIDEName,int iTimeOut)
{
	AEDesc SetProjectEvent;
	int iError = CreateAppleEventForCodeWarrior(&SetProjectEvent,'MMPR','STrg',pIDEName);
	if (!iError) {
		// Set the target name in the parameter
		iError = AEPutParamPtr(&SetProjectEvent,'----','TEXT',pTargetName,(long)StringLength(pTargetName));
		if (!iError) {
			AEDesc MyReply;
			AEInitializeDesc(&MyReply);
			iError = AESend(&SetProjectEvent,&MyReply,kAEDontRecord+kAECanInteract+kAEQueueReply+kAENoReply,kAENormalPriority,iTimeOut,NULL,NULL);
			if (!iError) {
				AEDisposeDesc(&MyReply);
			}
		}
		AEDisposeDesc(&SetProjectEvent);
	}
	return iError;
}

/***************************************

	Open the project file
	If bAllowConversion is true, it will allow CodeWarrior to perform 

***************************************/

static int OpenProjectFile(const char *pFilename,const char *pIDEName,Word bAllowConversion,int iTimeout)
{
	FSRef MyRef;
	Boolean bIsDirectory;
	int iError = FSPathMakeRef(reinterpret_cast<const UInt8 *>(pFilename),&MyRef,&bIsDirectory);
	if (!iError) {
		if (bIsDirectory) {
			// Force an error if opening a directory
			iError = -1;			
		} else {
		
			// Create an "Open a document" event
			AEDesc OpenDocEvent;
			iError = CreateAppleEventForCodeWarrior(&OpenDocEvent,'aevt','odoc',pIDEName);
			if (!iError) {
								
				// The Generic open doc event has the ability to open multiple files, 
				// which is why it needs a list instead of a single parameter
				AEDescList MyDescList;
				iError = AECreateList(NULL,0,FALSE,&MyDescList);
				if (!iError) {
					// Add a FSRef to the list
					iError = AEPutPtr(&MyDescList,0,'fsrf',&MyRef,sizeof(MyRef));
					if (!iError) {

						// Insert the FSRef list to the "Open a Document" event
						iError = AEPutParamDesc(&OpenDocEvent,'----',&MyDescList);
						AEDisposeDesc(&MyDescList);
						if (!iError) {
						
							// Do I allow project conversion?
							const Word32 *pConversionRequest = g_NoYes;
							if (bAllowConversion) {
								++pConversionRequest;		// Switch to 'yes '
							}
							iError = AEPutParamPtr(&OpenDocEvent,'Conv','enum',pConversionRequest,sizeof(Word32));
							if (!iError) {
								// Create my reply description
								AEDesc MyReply;
								AEInitializeDesc(&MyReply);
								// Tell CodeWarrior to open the project file
								iError = AESend(&OpenDocEvent,&MyReply,kAEDontRecord+kAECanInteract+kAEQueueReply+kAENoReply,kAENormalPriority,iTimeout,NULL,NULL);
								if (!iError) {
									AEDisposeDesc(&MyReply);
								}
							}
						}
					}
				}
				AEDisposeDesc(&OpenDocEvent);
			}
		}
	}
	if (iError) {
		fprintf(stderr,"error: could not open file %s\n",pFilename);
	}
	return iError;
}

/***************************************

	Perform a file diff

***************************************/

static int DiffFiles(const char *pIDEName,const char *pParm1,const char *pParm2,Word bIgnoreWhiteSpace,Word bIgnoreCase,Word bSkipSameFiles,Word bCompareContents,int iTimeout)
{
	Boolean bDirectory1;
	FSRef Ref1;
	int iError = FSPathMakeRef(reinterpret_cast<const UInt8 *>(pParm1),&Ref1,&bDirectory1);
	if (iError) {
		fprintf(stderr,"error: cw diff: %s: no such file or directory\n",pParm1);
	} else {
		Boolean bDirectory2;
		FSRef Ref2;
		iError = FSPathMakeRef(reinterpret_cast<const UInt8 *>(pParm2),&Ref2,&bDirectory2);
		if (iError) {
			fprintf(stderr,"error: cw diff: %s: no such file or directory\n",pParm2);
		} else if (bDirectory1 != bDirectory2) {
			fprintf(stderr,"error: cw diff: cannot compare a file with a directory\n");
			iError = -1;
		} else {
		
			// Create the Diff File event
			AEDesc DiffFileEvent;
			iError = CreateAppleEventForCodeWarrior(&DiffFileEvent,'MMPR','CmpF',pIDEName);
			if (!iError) {
				// Add the parameters
				
				// First, the files to compare
				iError = AEPutParamPtr(&DiffFileEvent,'----','fsrf',&Ref1,sizeof(Ref1));
				if (!iError) {
					iError = AEPutParamPtr(&DiffFileEvent,'Cmpt','fsrf',&Ref2,sizeof(Ref2));
					if (!iError) {
					
						// Now, the parameters
						Boolean bParameter = static_cast<Boolean>(bIgnoreWhiteSpace);
						iError = AEPutParamPtr(&DiffFileEvent,'CmCS','bool',&bParameter,sizeof(bParameter));
						if (!iError) {
							bParameter = static_cast<Boolean>(bIgnoreCase);
							iError = AEPutParamPtr(&DiffFileEvent,'CmIX','bool',&bParameter,sizeof(bParameter));
							if (!iError) {
								bParameter = static_cast<Boolean>(bSkipSameFiles);
								iError = AEPutParamPtr(&DiffFileEvent,'CmDF','bool',&bParameter,sizeof(bParameter));
								if (!iError) {
									bParameter = static_cast<Boolean>(bCompareContents);
									iError = AEPutParamPtr(&DiffFileEvent,'CmTC','bool',&bParameter,sizeof(bParameter));
									if (!iError) {
									
										// Ready to go? Issue the "Diff Files" event
										AEDesc MyReply;
										AEInitializeDesc(&MyReply);
										iError = AESend(&DiffFileEvent,&MyReply,kAEDontRecord+kAECanInteract+kAEQueueReply+kAENoReply,kAENormalPriority,iTimeout,NULL,NULL);
										if (!iError) {
											AEDisposeDesc(&MyReply);
										}
									}
								}
							}
						}
					}
				}
				AEDisposeDesc(&DiffFileEvent);
			}
		}
	}
	return iError;
}

/***************************************

	Act upon a project file. The operations must be done in the order of Open, Set Target,
	Clean, Build, Close project, close CodeWarrior

***************************************/

static int PerformProjectOperations(const char *pFilename,const char *pTargetName,const char *pIDEName,
	Word bAllowConversion,Word bCleanProject,Word bBuildProject,Word bQuitCodeWarrior,Word bCloseProject,Word bShowWarnings,Word bShowErrors,const char *pErrorFile,int iTimeout)
{ 
	int iError = OpenProjectFile(pFilename,pIDEName,bAllowConversion,iTimeout);
	if (!iError) {
		if (pTargetName && (iError = SetBuildTarget(pTargetName,pIDEName,iTimeout))!=0) {
			fprintf(stderr,"error: could not change target\n");
		} else if (bCleanProject && (iError = CleanProject(pIDEName,iTimeout))!=0) {
			fprintf(stderr,"error: could not remove objects\n");
		} else if (bBuildProject) {
			AEDesc MyErrors;
			AEInitializeDesc(&MyErrors);
			iError = BuildTarget(&MyErrors,pIDEName);
			if (iError) {
				fprintf(stderr,"error: could not build the target\n");
			} else if ((bShowWarnings | bShowErrors)!=0) {
			
				// Build completed, show the errors/warnings if requested
				
				FILE *fp = stdout;
				if (pErrorFile) {
					if (IsThereAnyItems(&MyErrors)) {
						fp = fopen(pErrorFile,"w");
						if (!fp) {
							// Abort output
							bShowErrors = FALSE;
							bShowWarnings = FALSE;
							fprintf(stderr,"warning: could not open the errors and warnings output file\n");
						}
					}
				}
				// Print errors and warnings
				if (bShowWarnings) {
					PrintErrorsOrWarnings(&MyErrors,TRUE,fp);
				}
				if (bShowErrors) {
					PrintErrorsOrWarnings(&MyErrors,FALSE,fp);
				}
				if (fp) {
					if (fp!=stdout) {
						fclose(fp);
					}
				}
				// Was anything left?
				if (IsThereAnyItems(&MyErrors)) {
					iError = -1;
				}
			}
			AEDisposeDesc(&MyErrors);
		}
		
		// Let's close the project file
		if (bCloseProject) {
			iError = CloseProject(pIDEName,iTimeout);
			if (iError) {
				fprintf(stderr,"error: could not close the project\n");
			}
		}
		
		// Let's shut down CodeWarrior
		if (bQuitCodeWarrior) {
			iError = ShutDownCodeWarrior(pIDEName,iTimeout);
			if (iError) {
				fprintf(stderr,"error: could not quit the IDE\n");
			}
		}
	}
	return iError;
}

/***************************************

	Handle the -proj command

***************************************/

static int ProcessProjCommand(int argc,char **argv,int *pIndex)
{
	const char *pTargetName = NULL;
	const char *pIDEName = NULL;
	const char *pErrorFile = NULL;
	Word bAllowConversion = 0;
	int iTimeout = kAEDefaultTimeout;
	Word bCleanProject = 0;
	Word bBuildProject = 0;
	Word bQuitCodeWarrior = 0;
	Word bCloseProject = 0;
	Word bShowWarnings = 0;
	Word bShowErrors = 0;
	int iIndex = *pIndex;
	for (;iIndex<argc;++iIndex) {
	
		// Is this a parameter list? "-bcd"
		const char *pArg = argv[iIndex];
		if ((pArg[0]=='-') && pArg[1]) {
			// Step through all the letters and set the flags accordingly
			size_t i;
			WordPtr MaxLen = StringLength(pArg);
			for (i=1;i<MaxLen;++i) {
				switch(pArg[i]) {
				case 'x':
					bAllowConversion = 1;
					break;
				case 'r':
					bCleanProject = 1;
					break;
				case 'b':
					bBuildProject = 1;
					break;
				case 'q':
					bQuitCodeWarrior = 1;
					break;
				case 'c':
					bCloseProject = 1;
					break;
				case 'z':
					if ((++iIndex)>=argc) {
						fprintf(stderr,"warning: no target specified\n");
					} else {
						pTargetName = argv[iIndex];
					}
					break;
				case 'w':
					bShowWarnings = 1;
					break;
				case 'e':
					bShowErrors = 1;
					break;
				case 'f':
					if ((++iIndex)>=argc) {
						fprintf(stderr,"warning: no errors and warnings output filename specified\n");
					} else {
						pErrorFile = argv[iIndex];
					}
					break;
				case 't':
					if ((++iIndex)>=argc) {
						fprintf(stderr,"warning: no timeout specified\n");
					} else if (!StringCompare("never",argv[iIndex])) {
						iTimeout = kNoTimeOut;
					} else {
						iTimeout = atoi(argv[iIndex])*60;
					}
					break;
				case 'y':
					if ((++iIndex)>=argc) {
						fprintf(stderr,"warning: no ide specified\n");
					} else {
						pIDEName = argv[iIndex];
					}
					break;
				default:
					fprintf(stderr,"notice: invalid option :'%c'\n",pArg[i]);
				}
			}
		} else {
		// Is this a valid project file argument? (More than one letter long)?
			if (pArg[1]) {
				// Jump to the code below
				break;
			}
			fprintf(stderr,"notice: ignoring project argument \"%s\"\n",pArg);
		}
	}
	
	int iError;
	if (iIndex>=argc) {
		fprintf(stderr,"error: no project file specified\n");
		iError = -1;
	} else {
		// Open and process the file
		iError = PerformProjectOperations(argv[iIndex],pTargetName,pIDEName,bAllowConversion,bCleanProject,bBuildProject,bQuitCodeWarrior,
		bCloseProject,bShowWarnings,bShowErrors,pErrorFile,iTimeout);
		++iIndex;
	}
	// Return the adjusted argc index
	*pIndex = iIndex;
	return iError;
}

/***************************************

	Handle the -diff command line

***************************************/

static int ProcessDiffCommand(int argc,char **argv,int *pIndex)
{
	Word bSkipSameFiles = TRUE;
	Word bIgnoreCase = FALSE;
	Word bIgnoreWhiteSpace = FALSE;
	const char *pIDEName = NULL;
	int iTimeout = kAEDefaultTimeout;
	int iIndex = *pIndex;
	for (;iIndex<argc;++iIndex) {
		// Is it a parameter list "-ibs"?
		const char *pArg = argv[iIndex];
		if (pArg[0]=='-' && pArg[1]) {
			size_t i;
			size_t MaxLen = StringLength(pArg);
			for (i=1;i<MaxLen;++i) {
				switch (pArg[i]) {
				case 'b':		// Ignore extra whitespace
					bIgnoreWhiteSpace = TRUE;
					break;
				case 'i':		// Ignore case
					bIgnoreCase = TRUE;
					break;
				case 's':		// Display same files
					bSkipSameFiles = FALSE;	
					break;
				case 'y':
					if ((++iIndex)>=argc) {
						fprintf(stderr,"warning: cw diff: no ide specified\n");
					} else {
						pIDEName = argv[iIndex];
					}
					break;
				case 't':
					if ((++iIndex)>=argc) {
						fprintf(stderr,"warning: no timeout specified\n");
					} else if (!StringCompare(argv[iIndex],"never")) {
						iTimeout = kNoTimeOut;
					} else {
						iTimeout = atoi(argv[iIndex])*60;
					}
					break;
				default:
					fprintf(stderr,"notice: cw diff: invalid option :'%c'\n",pArg[i]);
					break;
				}
			}
		} else if (pArg[1]!=0) {
			break;
		} else {
			fprintf(stderr,"notice: cw diff: ignoring project argument \"%s\"\n",pArg);
		}
	}
	// Perform the diff
	int iResult;
	if (iIndex>=argc) {
		fprintf(stderr,"error: cw diff: no files to compare\n");
		iResult = -1;
	} else if ((iIndex+1)>=argc) {
		fprintf(stderr,"error: cw diff: missing operand\n");
		iResult = -1;
	} else {
		iResult = DiffFiles(pIDEName,argv[iIndex],argv[iIndex+1],bIgnoreWhiteSpace,bIgnoreCase,bSkipSameFiles,TRUE,iTimeout);
		iIndex+=2;
	}
	*pIndex = iIndex;
	return iResult;
}

/***************************************

	Print the version information

***************************************/

static void PrintVersion(void)
{
	printf("cmdide version %s %s\n"
		"by: Josef W. Wankerl and Rebecca Ann Heineman\n"
		"Copyright (c) 2005, All rights reserved.\n",g_Version,g_BuildNumber);
}

/***************************************

	Call CodeWarrior from an OSX command shell
	Very useful for scripted builds

***************************************/

int BURGER_ANSIAPI main(int argc,char **argv)
{
	int iResult = 0;
	if ((argc<2) || (!StringCompare("--help",argv[1]))) {

		// Print the instructions
		PrintVersion();
		printf("\nUsage:\n"
			"  %s\n"
			"    --help             print this message\n"
			"    --version          print the version of cmdide\n"
			"\n"
			"    -diff [-ibs] [-y idepath] source destination\n"
			"      -i               ignore case\n"
			"      -b               ignore extra whitespace\n"
			"      -s               display files that are the same\n"
			"                       when comparing directories\n"
			"      -t timeout       specify a number of seconds to wait for an ide reply\n"
			"      -y idepath       use a specific ide by its pathname\n"
			"\n"
			"    -proj [-bceqrwx] [-t timeout] [-y idepath] [-z targetname] projectfile\n"
			"      -x               convert project when opening\n"
			"      -r               remove objects from project\n"
			"      -t timeout       specify a number of seconds to wait for an ide reply\n"
			"      -y idepath       use a specific ide by its pathname\n"
			"      -z targetname    switch to named target\n"
			"      -w               print build warnings\n"
			"      -e               print build errors\n"
			"      -f filename      send errors and warnings output to a file\n"
			"      -b               build target\n"
			"      -c               close target after building\n"
			"      -q               quit IDE after building\n",g_AppName);
	} else {
		int iIndex=1;
		if (iIndex<argc) {
			do {
				if (!StringCompare("--version",argv[iIndex])) {
					PrintVersion();
					++iIndex;
				} else if (!StringCompare("-diff",argv[iIndex])) {
					++iIndex;
					iResult = ProcessDiffCommand(argc,argv,&iIndex);
				} else if (!StringCompare("-proj",argv[iIndex])) {
					++iIndex;
					iResult = ProcessProjCommand(argc,argv,&iIndex);
				} else {
					iResult = OpenProjectFile(argv[iIndex],0,FALSE,0xFFFF);
					++iIndex;
				}
			} while (iIndex<argc);
		}
	}  
	return iResult;
}
