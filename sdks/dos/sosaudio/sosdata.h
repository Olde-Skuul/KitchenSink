/****************************************************************************

   File              : sosdata.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : 

   Last Updated      :

****************************************************************************
               Copyright(c) 1993,1994 Human Machine Interfaces 
                            All Rights Reserved
****************************************************************************/

#ifndef INCLUDED_SOSDATA_H
#define INCLUDED_SOSDATA_H

#ifndef INCLUDED_STDDEF_H
#include <stddef.h>
#endif

#include <pshpack4.h>

extern _SOS_SYSTEM _sSOSSystem;
extern _SOS_TIMER_SYSTEM _sTIMERSystem;
extern _SOS_DET_SYSTEM _sDETSystem;
extern PSTR _pSOSErrorStrings[];
extern W32 _wSOSDMAPortList[];
extern VOID ( *_pSOSMixerStubs[ _SOS_MAX_DRIVERS ] )( VOID );
extern W32 _wSOSData1Start;
extern W32 _wSOSData1End;

#ifdef __cplusplus
extern "C" {
#endif
extern   W32 _wSOSData2Start;
extern   W32 _wSOSData2End;
extern   W32 _wSOSData3Start;
extern   W32 _wSOSData3End;
extern   W32 _wSOSData4Start;
extern   W32 _wSOSData4End;
extern   BYTE  _bTIMERInstalled;
extern   BYTE  _bTIMERDPMI;
extern   W32  wDetectPort;
extern   W32  wDetectIRQ;
extern   W32  wDetectDMA;
extern   W32  wDetectParam;
#ifdef __cplusplus
}
#endif 

#include <poppack.h>

#endif
