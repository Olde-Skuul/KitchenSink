#include <stdio.h>
#include <dos.h>
#include "x32.h"

/*
        This program demonstrates the use of the mouse function 
        _x32_mouse_init() and _x32_mouse_term().  

        Caution!!! This code is for demonstration purposes only.  If this 
        application were to be used on any system with Virtual memory, X32VM 
        or any DPMI host, all memory accessed by the function mous_func() 
        would have to be locked using the function _x32_memlock().  In this 
        case, that would include all code within mous_func(), 4 bytes at the 
        storage location for the variable n and any function such as __CHK 
        which is called by all functions created by the Watcom compiler.

*/

volatile int mouse_mask, mouse_state, mouse_x, mouse_y;

void _cdecl mous_func(int mask, int state, int posx, int posy)
{
  _x32_click(); /* Just a reminder that we have entered the ISR. */

  mouse_mask = mask;
  mouse_state = state;
  mouse_x = posx;
  mouse_y = posy;
}

main()
{
  int last_state = 0;

  if(_x32_mouse_init(&mous_func,-1) == 0)
  {
    printf("\nMouse driver failed to initialize");
    return 1;
  }

  while((bdos(11,0,0)&1) == 0) /*  loop until keyboard is hit   */
  {
    if(last_state != mouse_state)
    {
      last_state = mouse_state;
      printf("mouse state = %d and mouse mask = 0x%x -- @ %d,%d\n",
        mouse_state,mouse_mask,mouse_x,mouse_y);
    }
  }
  _x32_mouse_term();            /*  Shut off the mouse  */
  bdos(8,0,0);                  /*  flush keyboard input without echo   */
  return 0;
}


