/****************************************************************************

   File              : sosdefs.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : 

   Last Updated      :

****************************************************************************
               Copyright(c) 1993,1994 Human Machine Interfaces 
                            All Rights Reserved
****************************************************************************/

#ifndef INCLUDED_SOSDEFS_H
#define INCLUDED_SOSDEFS_H

#ifndef _FALSE
#define _FALSE 0
#endif

#ifndef _TRUE
#define _TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef _NULL
#define _NULL  0
#endif

#ifndef  VOID
#define  VOID           void
#endif
typedef  int            BOOL;
typedef  unsigned int   UINT;
typedef  unsigned char  BYTE;
typedef  unsigned short WORD;
typedef  unsigned int   W32;
typedef  unsigned int   HFILE;
typedef  unsigned short W16;
typedef  unsigned short HSOS;
#ifndef  LONG
typedef  signed long    LONG;
#endif
typedef  unsigned long  DWORD;

typedef  BYTE  *        PBYTE;
typedef  char near *    PSTR;
typedef  WORD  *        PWORD;
typedef  unsigned short  * PSHORT;
typedef  LONG  *        PLONG;
typedef  VOID  *        PVOID;
typedef  HSOS *         PHSOS;

typedef  BYTE  far   *  LPBYTE;
typedef  BYTE  far   *  LPSTR;
typedef  WORD  far   *  LPWORD;
typedef  W32   far   *  LPW32;
typedef  LONG  far   *  LPLONG;
typedef  VOID  far   *  LPVOID;

typedef  BYTE  huge  *  HPBYTE;
typedef  BYTE  huge  *  HPSTR;
typedef  LONG  huge  *  HPLONG;
typedef  VOID  huge  *  HPVOID;

typedef  unsigned       HANDLE;

#endif
