#include "x32.h"
#include <stdio.h>
#include <stdlib.h>

#pragma ZTC align 1

/* the following prototypes should go in X32.H */

unsigned int _cdecl _x32_real_alloc(unsigned int size);
void _cdecl _x32_real_free(unsigned int rptr);
unsigned short _cdecl _x32_real_offset(unsigned int real_ptr);
void * _cdecl _x32_real_to_protected(unsigned int real_ptr);
unsigned int _cdecl _x32_dosmemleft();
unsigned int _cdecl _x32_real_coreleft();

/* these should stay here. */

static unsigned int rptrtophy(unsigned int rptr);
extern unsigned int _cdecl _x32_alloc_real_memory(unsigned int);
static unsigned int _cdecl _x32_realadd(unsigned int addr,int add);


#define PHY(x) (rptrtophy(x))
#define P(x) ((ML)_x32_real_to_protected(x))

struct memlink
{
	unsigned int n; /* next */
	unsigned int s; /* size */
	char p[4];
};

typedef struct memlink * ML;


unsigned int memhandle=0;



#ifndef NDEBUG
/*---------------------------------------------------------*/
/*							   */
/*							   */
/*---------------------------------------------------------*/


void seeall(char *s)
{
	unsigned int cblock;


	cblock=memhandle;

	printf("! %s  ",s);
	while(cblock!=0)
	{
		printf(" (phy:0x%X next:0x%X len:0x%X) ",
			PHY(cblock),PHY(P(cblock)->n),P(cblock)->s);
		cblock=P(cblock)->n;
	}
	printf("\n");
}
#endif


/*---------------------------------------------------------*/
/*							   */
/*							   */
/*---------------------------------------------------------*/

unsigned int _cdecl _x32_real_alloc(unsigned int size)

/*
This returns a 32-bit real mode pointer to real mode
memory in the form of an unsigned int.	If the return
value is 0 then the request failed.  This pointer may be
passed directly to real mode code as is or broken up
into a segment and offset by using the functions
_x32_real_segment() and _x32_real_offset().

'size' is the size of the real mode memory requested in
bytes.	The real mode memory can be addressed from
protected mode by using the protected mode pointer
returned from _x32_real_to_protected().

Real mode memory can be freed using _x32_real_free().
Freed memory is not returned to the operating system or
DOS extender, but is kept in a 'real heap' for later
allocation via calls to _x32_real_alloc().
*/

{
	unsigned int ret,     /* what to return */
	             blocks,  /* number of 4 Kbyte blocks */
	             pblock,  /* previous real addr */
	             cblock;  /* current real addr */

	if (size==0) return(0);    /* they didn't want any? */

	pblock=0;
	cblock=memhandle; /* cblock points at first free memory */
	
	while (cblock!=0)
	{
#if 0
		printf("   %d <? %d\n",size,P(cblock)->s);
#endif

		if (P(cblock)->s==size)
		{
			if (pblock==0) memhandle=P(cblock)->n;
			       else P(pblock)->n=P(cblock)->n;
			return(_x32_realadd(cblock,8));
		}
		
		if (P(cblock)->s>=size+8)
		{
			P(cblock)->s-=(size+8);
			pblock=_x32_realadd( cblock, P(cblock)->s+8 );
			P(pblock)->s=size;

			return( _x32_realadd(pblock,8) );
		}

		pblock=cblock;
		cblock=P(cblock)->n;
	}

	/* at this point, pblock points to the last member of
	   the linked list, and we must alloc more from dos. */

/*8*/	blocks = ( (size+8) + 0x0FFF)/0x1000; /* how many blocks? */
	ret = _x32_alloc_real_memory(blocks*0x100); /* beg dos */
	if (ret==0) return(0); /* out of memory... fail. */
	ret = ret << 16; /* fix address */


	P(ret)->n=0;
	P(ret)->s=blocks*0x1000-8;


	if (pblock==0) memhandle=ret;      /* hook this chunck */
	else P(pblock)->n=ret;             /* into the linked list. */
	
#if 0
	seeall("\nafter new");
#endif
	
	/* recurse. */
	return(_x32_real_alloc(size)); /* split it up on the next pass */
}

static unsigned int _cdecl _x32_realadd(unsigned int addr,int add)

/* add an offset to a real address, keep segment from
   being mangled. */
{
	unsigned int seg;
	long int off;

	seg=(addr&0xFFFF0000)>>16;
	off=(addr&0xFFFF)+add;

	while (off>0xFFFF)
	{
		seg++;
		off-=0x10;
	}
	while (off<0x0000)
	{
		seg--;
		off+=0x10;
	}
	return ((seg<<16)|off);
}




static unsigned int rptrtophy(unsigned int rptr)

/* convert a real pointer (32 bit format with upper 16 = seg, and lower
  16 = offset)	into a physical address */
{
    return((unsigned int)( (rptr&0xFFFF0000) >> 12) + (rptr&0x0000FFFF));
}


/*---------------------------------------------------------*/
/*							   */
/*							   */
/*---------------------------------------------------------*/

void _cdecl _x32_real_free(unsigned int rptr)

/*
Free a real mode pointer allocated via
_x32_real_alloc().  This memory is not actually returned
to the DOS extender or the operating system, it is kept
in a 'real heap' for later allocation via calls to
_x32_real_alloc().
*/

{
	unsigned int cblock,pblock,cblocka,pblocka;

	cblock=memhandle;
	pblock=0;

	while ( cblock != 0 ) /* find end of list */
	{
		pblock=cblock;
		cblock=P(cblock)->n;
	}

	rptr=_x32_realadd(rptr,-8);
	
	if (pblock==0) memhandle=rptr;  /* add freed part to end */
	  else P(pblock)->n=rptr;
	P(rptr)->n=0;

	/* next, go through the list and see if we can combine */
	/* any of the parts. */

	pblock=0;
	cblock=memhandle;
	while (cblock != 0)
	{
		pblocka=0;
		cblocka=memhandle;
		while (cblocka != 0)
		{
			if (PHY(cblock)+P(cblock)->s+8==PHY(cblocka))
			{
				if (pblocka==0)
				    memhandle=P(cblocka)->n;
				else
				    P(pblocka)->n=P(cblocka)->n;
				P(cblock)->s+=(8+P(cblocka)->s);
			}

			pblocka=cblocka;
			cblocka=P(cblocka)->n;
		}
	
		pblock=cblock;
		cblock=P(cblock)->n;
	}
}			

/*---------------------------------------------------------*/
/*							   */
/*							   */
/*---------------------------------------------------------*/
unsigned short _cdecl _x32_real_segment(unsigned int real_ptr)

/*
This returns the segment portion of the real mode
pointer 'real_ptr' which is normally obtained using the
function _x32_real_alloc().  This is roughly equivalent
to the function/macro FP_SEG() found in some compiler
runtime libraries or header files.
*/
{
	return( (unsigned short) ( ( ( real_ptr&0xFFFF0000 ) >>16 ) ) );
}

/*---------------------------------------------------------*/
/*							   */
/*							   */
/*---------------------------------------------------------*/

unsigned short _cdecl _x32_real_offset(unsigned int real_ptr)

/*
This returns the offset portion of the real mode pointer
'real_ptr' which is normally obtained using the function
_x32_real_alloc().  This is roughly equivalent to the
function/macro FP_OFF() found in some compiler runtime
libraries or header files.
*/
{
	return( (unsigned short) ( real_ptr&0x0000FFFF ) );
}

/*---------------------------------------------------------*/
/*							   */
/*							   */
/*---------------------------------------------------------*/

void * _cdecl _x32_real_to_protected(unsigned int real_ptr)

/*
This returns a protected mode pointer to the real mode
memory represented by the real mode pointer 'real_ptr',
normally this is allocated via _x32_real_alloc().  The
format of the real pointer is a 32-bit quantity in
SEGMENT:OFFSET format.	Hence the 'real_ptr' passed need
not be allocated from _x32_real_alloc(), but could also
have been something like 0xA0000000, which would be the
start of the EGA/VGA video buffer in graphics mode.
*/

{
	unsigned int seg,off;

	seg = (real_ptr >> 16);
	off = (real_ptr) & 0xFFFF;
	return( (void *)(
		(unsigned int)_x32_zero_base_ptr + (seg<<4) + off) );
}



unsigned int _cdecl _x32_real_coreleft()
{
	unsigned int corefree;
	unsigned int cur;

	corefree=_x32_dosmemleft()*16;
	cur=memhandle;

	while (cur!=0)
	{
		corefree+=P(cur)->s;
		cur=P(cur)->n;
	}

	return(corefree);
}

#ifdef RA_TEST

/* STRESS TEST */

#if 0
#define SHOW(X)\
   printf("start=%X len=%X start->s=%X", \
	PHY(start),len, P( _x32_realadd(start ,-8) )->s ); \
   if (last!=0) \
      printf(" last=%X lastlen=%X last->s=%X", \
	PHY(last),lastlen, P( _x32_realadd(last ,-8) )->s); \
   printf("\n"); \
   seeall(X)
#else
#define SHOW(X)\
   printf("start=%X len=%X start->s=%X", \
	PHY(start),len, P( _x32_realadd(start ,-8) )->s ); \
   if (last!=0) \
      printf(" last=%X lastlen=%X last->s=%X", \
	PHY(last),lastlen, P( _x32_realadd(last ,-8) )->s); \
   printf("\n")
#endif

void main(int argc,char *argv[])
{
	unsigned int total;
	unsigned int lop;
	unsigned int len;
	unsigned int lastlen=0;
	unsigned int last=NULL;
	unsigned int count;
	unsigned int start;
	unsigned char *pptr;


	total=_x32_real_coreleft();
	printf("total = %d\n",total);

/*	srand(9); */
	srand(4);

	for (count=0;count<200;count++)
	{
		printf("\n\n");

		start=_x32_real_alloc(len=rand());
		while (start==NULL)
		{
			printf("Not enough memory left, half request\n");
			len/=2;
			if (len<4)
			{
				printf("giving up.\n");
				exit(1);
			}
			start=_x32_real_alloc(len);
		}
		
		pptr=(unsigned char *)_x32_real_to_protected(start);


		SHOW("A:");
	
		for (lop=0;lop<len;lop++)
		{
			pptr[lop]=lop%0xFF;
		}

		printf("  DONE writing...");fflush(stdout);

		for (lop=0;lop<len;lop++)
		{
			if (pptr[lop]!=lop%0xFF)
			{
				printf("\n\nERR:\nlop=%d, lopFF=%d\n pptr[lop]=%d, pptr=0x%p\n start=0x%X  count=%d  len=%d\n  last=%d  lastlen=%d P(last)->s=%d\n",
					lop,lop%0xFF,pptr[lop],pptr,PHY(start),count,len,PHY(last),lastlen,P(last)->s);
				seeall("B CRASH:");
				exit(1);
			}
		}


		printf("  DONE reading...");fflush(stdout);

		if (last != NULL)
		{
			pptr=(unsigned char *)_x32_real_to_protected(last);
			for (lop=0;lop<lastlen;lop++)
			{
				if (pptr[lop]!=lop%0xFF)
				{
					SHOW("C CRASH:");
					exit(1);
				}
			}
			_x32_real_free(last);
		}

		printf("  DONE checking last...");fflush(stdout);

		last=start;
		lastlen=len;
	}

	pptr=(unsigned char *)_x32_real_to_protected(last);

	for (lop=0;lop<lastlen;lop++)
	{
		if (pptr[lop]!=lop%0xFF)
		{
			printf("\n\n\n\n\nERR:\nlop=%d, lopFF, pptr[lop]=%d pptr=0x%p, last=0x%X, count=%d, lastlen=%d\n",
				lop,lop%0xFF,pptr[lop],pptr,last,count,lastlen);
			seeall("D CRASH:");
			exit(1);
		}
	}

	_x32_real_free(last);

	printf("\n\n\ntotal core at start was %d, now it is %d\n\n\n",
		total, _x32_real_coreleft() );
	seeall("end");
}

#endif
