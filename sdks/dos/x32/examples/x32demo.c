/****************************************************************************
To compile and link this program, use the following command line:

    ztc x32demo -mx fgp.lib x32v.lib

May 11, 1992
****************************************************************************/


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "fg.h"
#include "fg_cstm.c"

#define ESC 27

static char order_text[] =
"\nThis is a demo program for X-32VM, a 32-bit DOS extender from FlashTek,\n\
Inc.  To order or get more information you may contact FlashTek as follows:\n\
\n\
FlashTek, Inc.                        FlashTek, Ltd.\n\
121 Sweet Ave                         2 Hill Court\n\
Moscow, Idaho 83843                   Swingbridge Road\n\
                                      Grantham\n\
Orders: 800-397-7310                  Lincs\n\
Info:   208-882-6893                  NG31 7XY  England\n\
FAX:    208-882-7275\n\
Email:  x-32vm@proto.com              FAX: +44-476-61382\n\
                                      Voice: +44-476-74108\n";

static char intro_text[] =
"Used with a compatible compiler a 32-bit DOS extender makes 32-bit \"flat \
model\" programming a reality under MS-DOS.  All the usual graphics, BIOS \
and DOS functions found in an MS-DOS compiler are available.  All \
difficulties of interfacing to extended and expanded memory are completely \
hidden from the programmer and the end-user. This program is running in 32-\
bit protected mode and will display the escape from the 640 K and \
64 K segment limitations, ability to do graphics, virtual memory and \
general protection faults.  But first, an introduction... \
\n\
The absence of a true 32-bit operating system has left most DOS programmers \
without adequate support for the 32-bit processors available in modern \
personal computers. New operating systems are being developed which will \
provide better support for the increased capabilities of these new processors. \
However, there will continue to be a large number of users who desire to \
continue using 16-bit DOS operating systems on 32-bit machines.\
\n\
The X-32 DOS extender provides a simple method of extending 16-bit DOS to \
support 32-bit applications on computers with 80386 processors and above. X-32 \
is linked with the 32-bit application and serves as an extension to DOS. There \
are no other run time files required; everything is contained in the resultant \
executable. The license included with X-32 allows these executables to be \
distributed freely without royalty payments or any other fees. \
\n\
All DOS and BIOS calls from the application are filtered through X-32, which \
converts each 32-bit function call from the application to one or more 16-bit \
calls which are compatible with the 16-bit DOS operating system. The \
advantages include increased available memory, faster code and elimination of \
the need for far pointers. X-32 is much more compact than most DOS extenders. \
For small programs, X-32 executables will be only about 15 Kbytes larger than \
the equivalent large memory model real mode programs. For larger programs, the \
X-32 executable size is often smaller than the equivalent large memory model \
16-bit programs, due to the elimination of multiple instructions required to \
use far pointers. \
\n\
X-32 allocates extended memory from XMS, VCPI, DPMI, INT 15 and VDISK sources. \
The application (through the compiler's runtime library) can then allocate \
memory with calls to X-32 and does not need to be aware of the presence or \
absence of any of the previously mentioned memory management systems.  The \
goal has been to provide the programmers with an operating system interface \
which is essentially a 32-bit DOS. X-32 applications are compatible with the \
VCPI specification, which enables it to operate with most modern EMS \
emulators, such as 386MAX and EMM386.\
\n\
DPMI compatibility means X-32 applications will operate with Windows 3.0 \
and above in all three modes and also DOS windows within OS/2 2.0. The \
maximum physical memory X-32 applications can utilize is typically 64M \
bytes, as limited by the interface to BIOS call INT 15H function 88H, \
which returns the amount of extended memory. The limitations of the \
interface to VCPI and DPMI hosts result in a limit of over 1 Gbyte of \
memory. X-32VM contains a virtual memory manager and can make up to 3.5 \
GBytes available to the application.  This provides the programmer with a \
doorway into the future of 32-bit programming, while preserving \
compatibility with older operating systems back to DOS 3.0.";

void show_text(const char *p, const fg_coord_t y),
     demo_memory(void), demo_fault();

int main()
{
  fputs(order_text,stdout);
  fputs("Press any key to continue...  ", stdout);
  fflush(stdout);
  if(getch() == ESC)
    return 0;;

  if(!fg_init())
  {
    fputs("Unable to initialize graphics for X-32VM demo.\n", stdout);
    return 1;
  }

  if(fg_box_height(fg.displaybox) > 480)
    fg_set_15x19_font();

  show_text(intro_text,fg.displaybox[FG_Y2]);

  fg_term();

  demo_memory();
  demo_fault();
  fputs("\n\nThank you for considering FlashTek!\n",stdout);
  fputs(order_text,stdout);
  return 0;
}

void demo_fault(void)
{
  int cc;

  printf("\n\nWould you like a demo of a general protection fault? ");
  fflush(stdout);
  do
  {
    cc = toupper(getch());
    if(cc == ESC)
      exit(0);
  } while(cc != 'Y' && cc != 'N');

  while(cc == 'Y')  /* The while() is to force the reading from '*p'. */
  {
    char *p = 0;

    printf("\n\n\
A NULL pointer will now be created and an attempt to read from that location\n\
will be made.  This will cause a general protection fault and a register\n\
dump.  The demo will be over...  Press any key to continue.  ");

    fflush(stdout);
    if(getch() == ESC)
      exit(0);
    fputs("\n\n", stdout);
    fflush(stdout);
    cc = *p;
  }
}

void demo_memory(void)
{
  char buf[200], *p;
  unsigned int mem, mem_accessed, mem_available = _x386_coreleft();

  do
  {
    printf(
"\nWith your present configuration, %u bytes may be allocated in a single\n\
array.  If you have the environment variable TMP (or TEMP) set to a disk\n\
drive with very little space available, you may wish to set it to another\n\
disk which has more room for the virtual memory swap space.\n\n\
How many bytes would you like to allocate for the demo (0 will go on to\n\
the next part of the demo)?  ", mem_available);
    fflush(stdout);
    fgets(buf,sizeof(buf),stdin);
    sscanf(buf, "%u", &mem);
  }while(!isdigit(buf[0]) || mem > mem_available);

  if(mem == 0)
    return;

  p = malloc(mem);

  if(!p)
  {
    fputs("Fatal error in memory allocation.\n", stderr);
    exit(1);
  }

  fputs(
"The memory has been obtained from malloc, now it will be randomly accessed --\
\none byte at a time.\nPress any key to continue then another key to stop.\n",
stdout);

  if(getch() == ESC)
    exit(0);

  mem_accessed = 0;
  do
  {
    p[((rand() << 16) + rand()) % mem] = 0;

    if((++mem_accessed & 0xff) == 0)
    {
      printf("%u bytes accessed\n", mem_accessed);
      fflush(stdout);
    }
  }while(!kbhit());

  free(p);
  if(getch() == ESC)
    exit(0);
}

void put_line(const char *p, int n, fg_coord_t y)
{
  fg_coord_t x = 0;

  while(n-- && *p != '\n')
  {
    fg_putc(FG_LIGHT_WHITE,FG_MODE_SET,~0,FG_ROT0,x,y,*p++,fg.displaybox);
    fg_adjustxy(FG_ROT0,1,&x,&y,fg.charbox);
  }
}

const char *paragraph_end(const char *p)
{
  while(*p && *p != '\n')
    p++;

  return p;
}

#define MAX_VEL 2

void coord_clip(fg_coord_t *p, fg_coord_t *v1, fg_coord_t *v2,
                fg_coord_t min, fg_coord_t max)
{
  if(min > *p || *p > max)
  {
    fg_coord_t temp;

    if(*p < min)
      *p = min;
    else
    {
      if(*p > max)
        *p = max;
    }

    *v1 = (*v1 > 0? -1: 1) * (rand () % MAX_VEL);
    temp = MAX_VEL + (*v1 > 0? -*v1: *v1);
    *v2 = *v2 > 0? temp: -temp;
  }
}
/**************************************
Bounce a line off the edges of the clipbox
**************************************/
void bounce_line(fg_pbox_t clipbox)
{
  static fg_line_t line;
  static fg_color_t color;
  static fg_coord_t
         vel_x1 = 1,
         vel_y1 = 1,
         vel_x2 = MAX_VEL,
         vel_y2 = MAX_VEL;

  if(line[FG_X1] == 0 && line[FG_X2] == 0 && line[FG_Y1] == 0 &&
     line[FG_Y2] == 0)
  {
    fg_line_cpy(line,clipbox);
  }

  if(++color >= fg.nsimulcolor)
    color = 0;

  /* Create the new line. */
  line[FG_X1] += vel_x1; line[FG_X2] += vel_x2;
  line[FG_Y1] += vel_y1; line[FG_Y2] += vel_y2;

  coord_clip(&line[FG_X1],&vel_x1,&vel_y1,clipbox[FG_X1],clipbox[FG_X2]);
  coord_clip(&line[FG_Y1],&vel_y1,&vel_x1,clipbox[FG_Y1],clipbox[FG_Y2]);
  coord_clip(&line[FG_X2],&vel_x2,&vel_y2,clipbox[FG_X1],clipbox[FG_X2]);
  coord_clip(&line[FG_Y2],&vel_y2,&vel_x2,clipbox[FG_Y1],clipbox[FG_Y2]);

  /* Draw the new line. */
  fg_drawline(color, FG_MODE_SET, ~0, FG_LINE_SOLID, line);
  fg_flush();
}

int key_get(fg_coord_t ymax)
{
  if(ymax > 2 && !kbhit())
  {
    static char press_any[] = "PRESS ANY KEY TO CONTINUE...";
    fg_font_t old_font;
    const int n_col = fg.nsimulcolor;
    fg_coord_t x;
    fg_box_t clipbox;

    fg_get_font(&old_font);

    if(fg_box_height(fg.charbox) == 8)
      fg_set_6x7_font();
    else
      fg_set_8x8_font();

    x = (fg_box_width(fg.displaybox) -
         fg_box_width(fg.charbox) * (sizeof(press_any) - 1))/2;

    ymax -= fg_box_height(fg.charbox);
    fg_puts(FG_LIGHT_WHITE,FG_MODE_SET,~0,FG_ROT0,x,ymax,press_any,
            fg.displaybox);

    fg_set_font(&old_font);

    fg_make_box(clipbox,fg_box_width(fg.displaybox)/4,0,
      fg.displaybox[FG_X2] - fg_box_width(fg.displaybox)/4,ymax/2);

    while(!kbhit())
      bounce_line(clipbox);
  }
  fg_flush();
  return getch();
}


void show_text(const char *l, const fg_coord_t ystart)
{
  int w = fg_box_width(fg.displaybox)/fg_box_width(fg.charbox);
  const char *p;

  do
  {
    fg_coord_t y = ystart;

    fg_fillbox(FG_LIGHT_BLUE == -1? FG_BLACK:FG_LIGHT_BLUE,FG_MODE_SET,~0,
      fg.displaybox);

    p = paragraph_end(l);

    do
    {
      int w_left = (p - l > w)? w: p - l;

      if(p - l > w)
      {
        w_left = w;
        while(l[w_left] != ' ')   /* break on a word boundary. */
          w_left--;
      }
      else
        w_left = p - l;

      y -= fg_box_height(fg.charbox);
      put_line(l,w_left,y);
      l += w_left + 1;
    }while(l < p && y > 0);

    if(key_get(y) == ESC)
    {
      fg_term();
      exit(0);
    }
  } while(*p || l < p);
}


