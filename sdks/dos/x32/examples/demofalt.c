/*
        This is a demonstration of the function _x32_fault_intercept().  
        This program hooks faults specifying handler() as the fault handler 
        and then proceeds to cause a general protection fault.  In this 
        program, handler() dumps out the processor registers and calls exit.  

        In a real application, the fault handler may be used to switch from 
        graphics mode to video mode prior to termination or it can be used for 
        starting a new thread of execution, continuing indefinitely without 
        any need to return or terminate.

*/
#include <stdio.h>
#include <x32.h>

void _cdecl handler(struct FAULT_STRUC *fault)
{
  printf("\nFault # %d has been intercepted.",(int)(*fault).fault_num);
  printf("\n\neax = %.8xH  ebx = %.8xH  ecx = %.8xH  edx = %.8xH",
    (*fault).eax,(*fault).ebx,(*fault).ecx,(*fault).edx);
  printf("\n\nedi = %.8xH  esi = %.8xH  ebp = %.8xH",
    (*fault).edi,(*fault).esi,(*fault).ebp); 
  printf("\n\nds = %.4xH  es = %.4xH  fs = %.4xH  gs = %.4xH",
    (int)(*fault).ds,(int)(*fault).es,(int)(*fault).fs,(int)(*fault).gs);
  printf("\n\nss:esp = %.4x:%.8xH",(int)(*fault).ss,(*fault).esp);
  printf("\n\ncs:eip = %.4x:%.8xH",(int)(*fault).cs,(*fault).eip);
  exit(1);              /* Exit with error code.                */
}

main()
{
  char *p;
  _x32_fault_intercept(handler);
  p=NULL;
  p[0] = 0;                             /* Cause a general protection fault */
  printf("no fault has occurred");
}

