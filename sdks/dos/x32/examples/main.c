#include <stdlib.h>

extern int _cdecl asm_main(int argc, char *argv[]);


int main(int argc, char *argv[])
{
  return asm_main(argc,argv);
}
