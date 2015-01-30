; Copyright Doug Huffman
; Route 1 Box 54A
; Lenore, ID 83541

; February 18,1992
; FAX:   208-263-8772
; email: doug@proto.com


comment&
        32 bit Startup code for DOS extender.  This module must be linked 
        first since it determines the segment order for all segments in the 
        final executable.  This file is specifically designed for the Symantec 
        compiler.
&

includelib zlx.lod              ;stub loader

.386

public __x386_zero_base_ptr,__x386_zero_base_selector,__data_bottom,__x386_init
public __x386_break,__chkstack,__chkstk,__heapbottom,__pastdata,__acrtused
public __dosx_zero_base_selector,__exe_type,__dosx_zero_base_ptr,__x386_version
public _sbrk,__x32_zero_base_ptr,__x32_zero_base_selector,__x386_stacklow
public __x386_malloc,__x386_free

;define 16 bit segments first so they will be located at the beginning
;of the executable.

__X386_DATASEG_16      segment para use16 public 'DATA16'
;16 bit data segment for real mode and priv level 0 activities
        extrn __x386_dbg_hook:word
        dw      _TEXT           ;first word in extender code, used by loader
        dw      offset __x386_dbg_hook  ;debugger hook
__X386_DATASEG_16      ends

__X386_CODESEG_16       segment para use16 public 'CODE'
assume cs:__X386_CODESEG_16,ds:nothing,es:nothing,fs:nothing,gs:nothing,ss:nothing
extrn __x386_start:near,__x32_link_in_x32_lib:near
__start:
        jmp     __x386_start    ;jump to 16 bit initialization
__X386_CODESEG_16       ends

_TEXT   segment para public 'CODE' ;must be paragraph aligned here

extrn _malloc:near,_free:near
extrn __exit:near,_exit:near,_main:near,__cinit:near

_TEXT   ends

_DATA   segment dword   public  'DATA'

extrn __stack:dword,__psp:dword,__osmajor:byte,__osminor:byte,_errno:dword
extrn __argc:dword,__argv:dword,__envptr:dword,__x386_data_16_alias:word
extrn __8087:dword,__baslnk:dword

DGROUP  group   _TEXT,_DATA,_BSS,HUGE_BSS
__acrtused      equ     1234    ;cause linker to pull in this module.

__data_bottom   label byte
;CAUTION!!!, the variables __pastdata and __x386_baslnk must be located
;immediately after __x386_stacklow for compatibility with the coreleft
;function.
__x386_stacklow label   dword   ;used by call back things
__x386_break    dd      ?       ;used by alloca
__pastdata      dd      offset DGROUP:EEND      ;address of 1 past data segment
__x386_baslnk   dd      offset DGROUP:__baslnk  ;used by coreleft
__heapbottom    dd      offset DGROUP:EEND      ;lowest address in heap (used 
                                ;to detect free() errors and stack wrap)
__stk_param_ptr dd      ?       ;pointer to stack size parameter in cmd strg

__ss            dw      ?       ;storage for default SS

;debugger requires two variables below to be positioned together
__x32_zero_base_selector        label   word
__x386_zero_base_selector       label   word    ;for compatibility with V3.0
__dosx_zero_base_selector       dw      34h     ;writable segment, base = 0
__x32_zero_base_ptr             label   dword
__x386_zero_base_ptr            label   dword   ;for compatibility with V3.0
__dosx_zero_base_ptr            dd      0f0000000h
__x386_malloc                   dd      offset _malloc
__x386_free                     dd      offset _free

__x386_disp_base        dw      0               ;storage for _dispbase
__x386_version          dw      310h            ;DOSX version #
__exe_type              dw      10h             ;Set exe file type

null_code_ptr   db      13,10,'NULL code pointer called',13,10,24h
nomem           db      13,10,'Not enough memory',13,10,24h
badstk          db      13,10,'Bad stack size parameter',13,10,24h
stk_overflow    db      13,10,'Stack Overflow',13,10,24h

_DATA   ends

;now define the order of the remaining segments
XIB     segment dword public 'DATA'
XIB     ends
XI      segment dword public 'DATA'
XI      ends
XIE     segment dword public 'DATA'
XIE     ends
XCB     segment dword public 'DATA'
XCB     ends
XC      segment dword public 'DATA'
XC      ends
XCE     segment dword public 'DATA'
XCE     ends
CONST   segment dword public 'CONST'
CONST   ends
_BSS    segment dword public 'BSS'
_BSS    ends
HUGE_BSS        segment dword public 'HUGE_BSS'
HUGE_BSS        ends
EEND    segment para public 'ENDBSS'
EEND    ends

_TEXT   segment para public 'CODE'

if @Version LT 600
        assume  CS:_TEXT
endif
        assume  DS:DGROUP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;This is the very beginning of the 32 bit code segment.
;It must be paragraph aligned so that the offset of the first instruction
;will be zero.  If the address immediately below is ever called, it will be 
;due to an null code pointer.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        push    ebp
        mov     ebp,esp
        mov     edx,offset DGROUP:null_code_ptr
        jmp     prn_msg          ;exit with error message
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;This is the location where 16 bit code transfers control to when 
;first entering 32 bit code.  DS will = ES = __x386_data_32, GS = 
;__x386_seg_env, FS = __x386_seg_psp.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

__x386_init:
        mov     ebx,ds
        mov     ecx,offset DGROUP:__data_bottom[-1]     ;pointer to top of code
        mov     ax,3505h
        int     21h             ;set ds limit

        mov     __psp,fs
        mov     __ss,ss
        mov     bx,gs                   ;environment segment
        mov     ax,3504h                ;get address of selector in bx
        int     21h                     ;returns address in ecx
        add     ecx,__x386_zero_base_ptr ;convert to DGROUP relative
        mov     __envptr,ecx            ;Save this for now.

;initialize _BSS
        mov     ecx,offset DGROUP:EEND  ;end of _BSS
        mov     edi,offset DGROUP:_BSS  ;start of _BSS is in es:edi
        sub     ecx,edi                 ;size in bytes of _BSS
        shr     ecx,2                   ;size in dwords of _BSS
        xor     eax,eax                 ;zero the block
;EEND must be dword aligned for this to work
        cld
        rep     stosd

;now setup argv and argc
        xor     eax,eax
        xor     ebx,ebx
        mov     ds,__psp
        lea     esi,[eax+80h]           ;point to number of characters
        lodsb                           ;load the number of characters
        or      al,al
        jz      a1                      ;jmp if no command line
        push    0                       ;terminating zero for end of cmd line
        sub     esp,eax                 ;allocate space on stack for cmd line
        mov     edi,esp                 ;es:edi points to storage space
        mov     ebp,esp
        and     sp,0fffch               ;round down to nearest dword
        mov     ecx,eax                 ;number of bytes to move
        rep     movsb                   ;transfer command line to stack
        push    es
        pop     ds                      ;restore DS to DGROUP
        mov     esi,ebp                 ;ds:esi points to string

a3:     ;next non white space may be a possible arg
        lodsb                           ;load a character in al
        cmp     al,0                    ;check if end of string
        je short a1
        cmp     al,' '                  ;check for a space
        je      a3
        cmp     al,9                    ;check for a tab
        je      a3
        cmp     al,'"'                  ;check for a "
        je short a2
        cmp     al,"'"                  ;check for a '
        je short a2
        cmp     al,'='                  ;check for a =
        je      stack_arg_found
a8:
;if we reach this point, esi points to one past a valid arg
        mov     ecx,esi
        dec     ecx
        push    ecx                     ;push pointer to arg
        inc     ebx                     ;indicate one more pointer on stack
a5:     ;search for next white space
        lodsb
        cmp     al,0                    ;check if end of string
        je short a1
        cmp     al,' '                  ;check for a space
        je      a4
        cmp     al,9                    ;check for a tab
        jne     a5
a4:     ;we have found the end of an arg string, place a terminating zero
        mov byte ptr ds:[esi-1],0       ;mark end of string
        jmp short a3

a2:     ;A  '  or  "  has been found, esi points to valid arg
        ;find next match before returning
        push    esi                     ;pointer to arg
        inc     ebx                     ;indicate one more pointer on stack
        mov     ah,al                   ;character to search for
a6:     lodsb
        cmp     ah,al
        je      a4                      ;jmp if end has been found
        cmp     al,0
        jne     a6                      ;loop if not at end of command string

a1:     ;ebx has number of command line arg pointers pushed on the stack
;The pointers are in reverse order of what we need.  We need to allocate
;space for two extra pointers, one for argv[0] which points to the program
;name and one for a terminating null pointer in the array of pointers.
        push    es
        pop     ds                      ;restore ds in case of no parameters
        push    0                       ;terminating null pointer
        inc     ebx                     ;allow for terminating null pointer
        lea     eax,[ebx*4+4]           ;allow bytes for argv[0]
        push    eax                     ;number of bytes to allocate
        call    _malloc                 ;allocate space for pointers
        pop     ecx                     ;pop number of bytes off stack
        or      eax,eax
        jz      insuf_mem
        mov     __argv,eax
        mov     __argc,ebx
        push    ds
        pop     es
        lea     edi,[eax+ecx-4]         ;pointer to last dword allocated
        mov     ecx,ebx                 ;number of pointers
comment&
        Code below copies pointers for argv to storage in reverse order of
        what is on the stack.  The first item off the stack is the calling 
        parameter to malloc (garbage) and takes the place of argv[0] which 
        will be initialized later.
&
        std                             ;set direction flag
a7:     pop     eax                     ;pop a pointer off the stack
        stosd                           ;place it in storage
        loop    a7
        cld                             ;restore the direction flag
;argv and argc are now set up except for argv[0].
        mov     edi,__envptr            ;es:edi points to environment
        mov     ecx,edi                 ;guaranteed to be a big number
        xor     eax,eax
e1:
        repne   scasb                   ;search for a zero
        scasb                           ;check for a second zero
        jne     e1
;when execution reaches this point, edi will point to 1 past the second zero.
        lea     edi,[edi+2]             ;point to program name
        mov     eax,__argv
        mov     ds:[eax],edi            ;initialize argv[0]
;reserve space for stack

        mov     edx,__stack
        mov     ecx,16*1024
        cmp     ecx,edx
        ja short s1
        mov     ecx,edx                 ;use the largest of __stack or 16k
s1:     mov     ax,350dh                ;setup stack
        mov     ebx,esp
;call with ecx = desired size of stack, ebx = present esp value
;returns new esp in ebx and recommended limit for ss in edx
        int     21h
        jc      insuf_mem
        mov     esp,ebx                 ;switch to new stack
        mov     ecx,edx                 ;new limit for ss
        mov     ebx,ss
        mov     ax,3505h                ;set selector limit

        int     21h
        mov     ah,30h                  ;get DOS version number
        int     21h
        mov     __osminor,ah
        mov     __osmajor,al

        call    __x386_coproc_init      ;initialize coprocessor
        xor     eax,eax
        mov     fs,eax
        mov     gs,eax                  ;make mode switches faster
        push    eax                     ;ebp value for last stack frame
        mov     ebp,esp

        call    init_envp               ;Malloc space for environment.

        call    __cinit         ;perform static constructors
        push    __argv
        push    __argc
        call    _main           ;call _main(__argc,__argv)
        push    eax             ;push exit status
        call    _exit
;no return from _exit

stack_arg_found:                ;esi points to first character in stack arg
        cmp     __stack,0
        je      a8                      ;return if =nnn feature is disabled
        push    esi                     ;store esi
        xor     edx,edx                 ;accumulator for stack size
        xor     eax,eax                 ;zero high 3 bytes of eax
s3:
        lodsb                           ;load a character after the =
        cmp     al,0                    ;check for terminating zero
        je short s5
        cmp     al,' '                  ;check for space
        je short s8
        cmp     al,9                    ;check for a tab
        je short s8
        sub     al,48                   ;convert ascii to decimal
        jb short bad_stk
        cmp     al,9
        ja short bad_stk
        imul    edx,10
        add     edx,eax
        jmp short s3

s8:     or      edx,edx                 ;check if zero
        jz short s6

        mov     __stack,edx             ;new value from command line
        pop     edx                     ;pop original esi off stack
        jmp     a3

s5:     ;found end of command string
        dec     esi                     ;so arg setup code will find termination
        jmp     s8

s6:     ;command line stack size was zero, use it for an arg
        pop     esi                     ;restore esi
        jmp     a8

bad_stk:        ;bad stack size parameter
        mov     edx,offset DGROUP:badstk
        jmp short prn_msg

insuf_mem:
        mov     edx,offset DGROUP:nomem

prn_msg:
        mov     ah,9
        int     21h
        push    1               ;error exit code
        call    __exit          ;abort

comment&
        Sbrk is optimized for use with the Zortech libraries.  __pastdata is 
        used by Zortech libraries to test for a corrupted heap.  __pastdata 
        should always be above the highest block of memory in the pool.  A 
        peculiarity of Zortech's sbrk is that the actual size allocated may be 
        increased above requested and if so the actual size is returned on the 
        stack.  Sbrk is normally called with a request for a minimum of 
        16kbytes. 

 Allocate a block of memory from the operating system.

 sbrk(nbytes);  nbytes = number of bytes to allocate
 Returns:
       near pointer to memory allocated in eax
       -1 in eax if error
       size of memory block allocated on stack
&

_sbrk   proc    near
        mov     ecx,ss:[esp+4]  ;requested block size
        neg     ecx
        and     cx,0f000h       ;round up to nearest 4k boundary
        neg     ecx
        mov     ax,350ch        ;allocate memory
;function below allocates a block of memory of size = ecx.  If successful,
;CF = 0, eax points to new block, edx is new lowest legal value for esp.  If 
;unsuccessful, CF = 1.
        int     21h
        jc short sbrk_err               ;jmp if insufficient memory
        mov     __x386_break,edx
        mov     ss:[esp+4],ecx          ;return actual size of block
        add     ecx,eax                 ;point to top of block
        cmp     ecx,__pastdata
        jb short sbrk_ret
;__pastdata should be top most legal address on heap
        mov     __pastdata,ecx
sbrk_ret:
        ret

sbrk_err:
        sbb     eax,eax
        ret
_sbrk   endp

stack_overflow:
        mov     edx,offset DGROUP:stk_overflow
        jmp     prn_msg

Comment&
        The code below generates a special stack frame and is called when
        stack overflow checking is enabled.
&
__chkstk        proc    near
        neg     eax
        pop     edx             ;pop return address
        add     eax,esp         ;esp - eax = new esp value
        cmp     eax,__x386_break
        jbe     stack_overflow
        mov     esp,eax         ;allocate space for automatics
        jmp     edx             ;return
__chkstk        endp

comment&
        Function to return the memory available for the stack.
&
__chkstack      proc    near
        mov     eax,__x386_break
        neg     eax
        add     eax,esp         ;calculate how much memory left for stack
        ret
__chkstack      endp


comment&
        __get_video_selector returns a protected mode selector in ax which 
        points to the video buffer.  The real mode segment value is passed in 
        ax.  A protected mode selector is allocated with base address of 
        ax * 16, if no selectors are available it returns 0 in ax which causes 
        disp to use bios.  If zero was passed in AX, it returns 0 which tells 
        disp to use bios. 
&
public __get_video_selector
__get_video_selector       proc    near
        or      ax,ax           ;check for zero
        jz short vid_sel_ret    ;if zero, return zero
        push    ebx
        movzx   ecx,ax          ;segment address
        shl     ecx,4           ;make absolute address
        cmp     __x386_disp_base,0
        jnz short r1                    ;if not zero, it is already allocated
get_new_selector:
        mov     ax,3501h                ;allocate a selector
        int     21h
        jc short r3                     ;jmp if no selectors available
        mov     __x386_disp_base,BX     ;new selector
r1:     mov     ax,3503h                ;set address
        mov     bx,__x386_disp_base
        int     21h
        mov     ax,3505h                ;set limit
        neg     ecx
        add     ecx,100000h             ;give it a limit of 1 megabyte
        int     21h
r2:     movzx   eax,bx
        pop     ebx
vid_sel_ret:
        ret
r3:     xor     eax,eax                 ;return error
        pop     ebx
        ret
__get_video_selector    endp

;;;;;;;;;;;;;;;;;;;;;;;;;
; Allocate space for the environment via malloc().  This allows putenv() to
; reallocate if desired.
; September 29, 1992
;;;;;;;;;;;;;;;;;;;;;;;;;
init_envp       proc    near
        mov     eax,ds
        mov     es,eax
        mov     edi,__envptr

env_loop_top:
        xor     eax,eax
        mov     ecx,eax
        dec     ecx
        repne   scasb

        mov     al,[edi]        ;End of environment is two bytes of zeros.
        or      al,al           ;Is this the end?
        jnz     env_loop_top    ;Jump if not...

        add     edi,3           ;Start of the program name.
        repne   scasb           ;Find the end of the program name.
        sub     edi,__envptr    ;Calculate the size to malloc.

        push    edi
        call    _malloc
        add     esp,4

        or      eax,eax
        jz      insuf_mem

        mov     ecx,edi         ;Bytes to transfer.
        mov     esi,__envptr
        mov     __envptr,eax    ;New ptr to environment string.
        mov     edi,eax         ;Destination of transfer.
        rep     movsb           ;Transfer is now done.

        ret
init_envp       endp

comment&
        Code to detect presence of 287 or 387.  It assumes that an 8087 is not 
        possible.  This is adapted from the Intel book: 387 DX user's manual, 
        page 6-3.
&
__x386_coproc_init      proc    near
        fninit
        xor     ecx,ecx                         ;default is no coprocessor
        push    0ffffffffh                      ;dword nonzero
        fnstsw  ss:[esp+2]                      ;should give zero if coproc
        fnstcw  ss:[esp]
        pop     eax
        and     ax,103fh                        ;ax should = 3fh, high word 0
        cmp     eax,3fh
        jne     coproc_ret
;some type of coprocessor is present, determine if 287 or 387
        fstcw   word ptr __8087
        fld1
        fldz
        fdivp   st(1),st                        ;form infinity
        fld     st
        fchs                                    ;form negative infinity
;on 287, -infinity = +infinity on 387, -infinity != +infinity
        fcompp
        fstsw   ax
        or      byte ptr __8087[1],10h          ;turn on infinity bit
        fldcw   word ptr __8087
        mov     ecx,2                           ;at least a 287 is present
        sahf
        je      coproc_ret                      ;jmp if 287
        inc     ecx                             ;indicate 387
coproc_ret:
        fclex                                   ;clear error from divide by 0
        mov     __8087,ecx
        ret
__x386_coproc_init      endp

_TEXT   ends

end     __start

