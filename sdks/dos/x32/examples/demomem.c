#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "x32.h"

int main(int argc, char *argv[])
{
  static char msg1[]= "far pointer test";
  static char msg2[]= "near pointer test";
  int i = 0;
  int n;
  char *a;
  char _far *b;

/*
        First we will demonstrate how to use near pointers for accessing items 
        in the first megabyte.  We will calculate a pointer which points to 
        the video buffer and use it to write directly to the video buffer.

        This code assumes that the video buffer resides at absolute address 
        0xb8000. 
*/
  a = (char *)_x32_zero_base_ptr + 0xb8000;

  for(n=0; n < sizeof(msg2); ++n)
  {
    a[n*2]= msg2[n];     /* Place message on first line of video buffer */
  }

/*
        We will construct a far pointer to the video buffer and use it to 
        write directly to the video buffer.
*/
  b = _x32_mk_protected_ptr((void *)0xb8000);
  for(n=0; n < sizeof(msg1);  ++n)
  {
    b[n*2+160]=msg1[n];     /* Place message on second line of video buffer */
  }

/*  
        For demonstration purposes, we will convert the far pointer b into an 
        equivalent near pointer.
*/
  a =  (char *)_x32_zero_base_ptr + _x32_get_abs_address(b);
  for(n=0; n < sizeof(msg2);  ++n)
  {
    a[n*2+320]=msg2[n];     /* Place message on third line of video buffer */
  }

  printf("\nCoreleft returns %d\n",_x32_coreleft());

  return 0;
}

