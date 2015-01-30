/* Copyright FlashTek, Inc. 1994 */
/* 121 Sweet Ave. */
/* Moscow, Idaho  83843 */

/* Joe Huffman */
/* November 4, 1994 */
/* FAX:   208-882-7275 */
/* email: joe@proto.com */

#include <dos.h>

#ifdef __WATCOMC__
#include <malloc.h>
#endif

#if __ZTC__ || __SC__
typedef struct heap
{
  struct heap *next;
  size_t size;
} heap_t;
#endif

#include "x32.h"

/****************************************************************************
Return the largest block of memory that can be allocated in a single malloc().
November 4, 1994
****************************************************************************/
unsigned int _x386_coreleft(void) { return _x32_coreleft(); }
unsigned int _x32_coreleft(void)
{
  size_t ret_mem = 0, heap_mem = 0;
  union REGS r;

#if __WATCOMC__
  heap_mem = _memmax();
  r.w.ax = 0x350b;     /* Call the extender for info on available memory. */

  ret_mem = intdos(&r,&r);  /* This is only the extender memory. */
  if(ret_mem > 4)
    ret_mem -= 4;

#else /* If Zortech or Symantec. */

  r.x.ax = 0x350b;     /* Call the extender for info on available memory. */

  ret_mem = intdos(&r,&r);  /* This is only the extender memory. */
  if(ret_mem > 4)
    ret_mem -= 4;

  {
    extern size_t _x386_stacklow[];
    heap_t *starting_heap_p = (heap_t *)_x386_stacklow[2];
    heap_t *heap_p;

#if 0
    /* Add memory between __pastdata and next higher 4K boundary. */
    ret_mem -= ((-_x386_stacklow[1]) & ~(0xffff)) + _x386_stacklow[4];
#endif

    heap_p = starting_heap_p;

    do
    {
      heap_p = heap_p->next;   /* Next pointer. */

      if(heap_p->size > heap_mem)
        heap_mem = heap_p->size;

    } while(heap_p != starting_heap_p);

    if(heap_mem >= 4)
      heap_mem -= 4;   /* Minus malloc overhead. */
    else
      heap_mem = 0;
  }
#endif

  return heap_mem > ret_mem ? heap_mem: ret_mem;
}

/****************************************************************************
Return the total amount of memory available.  This may not be contigious 
memory -- it may require more than one memory allocation call.
November 4, 1994
****************************************************************************/
unsigned int _x386_allcoreleft(void) { return _x32_allcoreleft(); }
unsigned int _x32_allcoreleft(void)
{
  size_t ext_mem, heap_mem = 0;
  union REGS r;

#ifdef __WATCOMC__
  r.w.ax = 0x350b;     /* Call the extender for info on available memory. */

  heap_mem = _memavl();
#else /* If Zortech or Symantec. */

  r.x.ax = 0x350b;     /* Call the extender for info on available memory. */
  {
    extern size_t _x386_stacklow[];
    heap_t *starting_heap_p = (heap_t *)_x386_stacklow[2];
    heap_t *heap_p;

#if 0
    /* Add memory between __pastdata and next higher 4K boundary. */
    heap_mem -= ((-_x386_stacklow[1]) & ~(0xffff)) + _x386_stacklow[4];
#endif

    heap_p = starting_heap_p;

    do
    {
      heap_p = heap_p->next;   /* Next pointer. */

      if(heap_p->size > 4)
        heap_mem += heap_p->size - 4;

    } while(heap_p != starting_heap_p);
  }
#endif

  ext_mem = intdos(&r,&r);  /* This is only the extender memory. */

  return ext_mem + heap_mem;
}

#ifdef CORE_TEST
#include <stdio.h>

void report(const char *mess)
{
  size_t core = _x32_coreleft(), allcore = _x32_allcoreleft();
  printf("%s\ncore =    %u\nallcore = %u\n", mess, core, allcore);
}

int main()
{
  size_t core = 0;
  char *array[3];

  report("");
  report("\nAfter a printf:");

  array[0] = (char *)malloc(100);
  array[1] = (char *)malloc(100);
  array[2] = (char *)malloc(100);
  report("\nAfter 3 malloc(100):");

  free(array[1]);
  report("\nAfter a free:");

  free(array[0]);
  free(array[2]);

  report("\nAfter all freed:");

  core = _x32_coreleft();
  do
  {
    char buf[100];

    array[0] = (char *)malloc(core);

    if(array[0])
      sprintf(buf,"malloc(%d) succeeded:", core);
    else
      sprintf(buf,"malloc(%d) failed:", core);

    report(buf);

    core += _x32_coreleft()/2 + 1;
    free(array[0]);
  } while(array[0]);

  return 0;
}
#endif /* CORE_TEST */
