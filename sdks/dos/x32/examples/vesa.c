#include <stdio.h>  /* For fputs() and fputc(). */
#include <dos.h>    /* For int86x_real(). */
#include <string.h> /* For memset(). */

#include "x32.h"

unsigned int get_vesa_info(); 

int main()
{
  unsigned int vesa_real_p = get_vesa_info();

  if(vesa_real_p)
  {
    char *vesa_p = _x32_real_to_protected(vesa_real_p);
    unsigned int real_mode_oem_p = *(unsigned int *)(vesa_p + 6);
    char *oem_p = _x32_real_to_protected(real_mode_oem_p);

    printf("VESA OEM name = '%s'\n",oem_p);

    _x32_real_free(vesa_real_p);
  }
  return 0;
}

/****************************************************************************
Returns a real mode pointer to a 256 byte block of memory that contains the 
VESA info. This block of memory was allocated useing _x32_real_alloc() and 
must be freed with _x32_real_free().  If return value is 0, the call failed.
November 29, 1993
****************************************************************************/
unsigned int get_vesa_info(void)
{
  unsigned int real_ptr = _x32_real_alloc(256);

  if(real_ptr)
  {
    union _REGS reg;
    struct _SREGS seg;

    memset(&reg,0,sizeof(reg)); /* Just to initialize to known values. */
    memset(&seg,0,sizeof(seg));

    reg.x.ax = 0x4f00;
    reg.x.bx = 0;
    reg.x.di = _x32_real_offset(real_ptr);
    seg.es = _x32_real_segment(real_ptr);
    int86x_real(0x10,&reg,&reg,&seg);

    if(reg.x.ax != 0x4f)  /* Did call succeed? */
    {
      _x32_real_free(real_ptr); /* Call failed -- return failure result. */
      real_ptr = 0;
    }
  }

  return real_ptr;
}




