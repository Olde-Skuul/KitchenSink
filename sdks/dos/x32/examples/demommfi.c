/*
        This program demonstrates the use of the memory mapped file IO 
        functions.  This creates a file, maps it into memory and then flushes 
        the data to disk.  After exiting, there should be a file "tmptest" in 
        the default directory, 4096 bytes in size with the test message at the 
        beginning of the file.
*/

#include <string.h>
#include <io.h>

void * cdecl _x32_mmfio_open(int fd, int size);
int cdecl _x32_mmfio_flush(void *);

#if __WATCOMC__ >= 100  /* Needed only for Watcom 10.0 or greater. */
#include <stdlib.h>

void *(*_x386_malloc)(size_t s) = malloc;
void (*_x386_free)(void *p) = free;

#pragma aux _x386_malloc "_*";
#pragma aux _x386_free "_*";
#endif

main()
{
  int file1;
  char *p1, *msg = 
"This is a test message for memory mapped file IO.\n\
This message should appear in the file,\n\
tmptest which is created by this program";

  file1=creat("tmptest",0x180);
  if (file1 == -1)
  {
    printf("\nFailure attempting to create file tmptest");
    return 1;
  }
  p1=_x32_mmfio_open(file1, 1000);
  if(p1 == 0)
  {
    printf("\nFailure attempting to map file");
    close(file1);
    return 1;
  }
  strcpy(p1,msg);   /*  copy string to file  */
  if(_x32_mmfio_flush(p1))
  {
    printf("\nMemory mapped file IO has been successful");
    close(file1);
    return 0;
  }
  printf("\nFailure attempting to flush memory mapped file block");
  close(file1);
  return 1;
}

