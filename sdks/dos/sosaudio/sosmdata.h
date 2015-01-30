/****************************************************************************

   File              : sosmdata.h

   Programmer(s)     : Don Fowler

   Date              : 5/5/95

   Purpose           : Global data external definitions for the MIDI system

   Last Updated      : 5/5/95

****************************************************************************
               Copyright(c) 1992,1995 Human Machine Interfaces 
                            All Rights Reserved
****************************************************************************/

#ifndef INCLUDED_SOSMDATA_H
#define INCLUDED_SOSMDATA_H

#ifndef INCLUDED_SOSM_H
#include <sosm.h>
#endif

extern _MIDI_SYSTEM  _sMIDISystem;
extern _MIDI_DRIVER  _sMIDIDriver[];
extern W32 ( cdecl far * _lpMIDICBCKFunctions[] )( LPSTR, W32, W32 );
extern W32 ( cdecl far * _lpMIDIDIGIFunctions[] )( LPSTR, W32, W32 );
extern W32 ( cdecl far * _lpMIDIWAVEFunctions[] )( LPSTR, W32, W32 );
extern W32 _wMIDIDriverTotalChannels[];
extern W32 _wMIDIDriverChannel[ _MIDI_DEFINED_DRIVERS ][ _MIDI_MAX_CHANNELS ];
extern VOID ( cdecl far * _lpMIDICBCKFunction )( LPSTR, W32, W32 );
extern _MIDI_DIGI_CHANNEL _sMIDIDIGIChannel[];
extern _MIDI_DIGI_QUEUE_ELEMENT _sMIDIDIGIQueue[][ _MAX_VOICES ];
extern W32 _wMIDIDIGISampleQueueHead[];
extern W32 _wMIDIDIGISampleQueueTail[];
extern W32 _wMIDIDIGIMaxSamples[];
extern W32 _wMIDIDIGIUsedSamples[];
extern _MIDI_DIGI_SYSTEM _sSOSMIDIDIGIDriver[];
extern _MIDI_DIGI_QUEUE _sSOSMIDIDIGIQueue[]; 
extern W32 _wCData1Start;
extern W32 _wCData1End;

#endif
