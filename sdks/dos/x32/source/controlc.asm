comment &
        Copyright 1993   All rights reserved.
        FlashTek Inc.
        121 Sweet Ave.
        Moscow, ID  83843

        Voice:  208-882-6893
        FAX:    208-882-7275

        This file is a direct replacement for the Zortech file "controlc.asm" 
        which is located in the source\dos386 directory where the Zortech 
        compiler is installed.  This file fixes the following problems with 
        the Zortech code:

        1.  It locks its own code, data and stack for compatibility with 
            Virtual memory systems such as Windows and X-32VM.

        2.  It works around a Windows problem associated with intercepting 
            protected mode interrupts by only hooking real mode interrupts.

        3.  It works with stack checking turned on which the Zortech version 
            will not.
        
        Like the Zortech version, it is up to the user to lock the code and 
        data accessed by the user's controlc handler, and it is up to the user 
        to initialize the variable, "__controlc_handler" to point to the user 
        defined controlc handler. 
&

include mac32.asm

public _controlc_open,_controlc_close

start32data
public  __controlc_handler
__controlc_handler  dd  0           ;pointer to user defined handler
end32data
_BSS    segment dword public 'BSS'

data_16_alias   dw      0

stack_buf       db      1024 dup (0)    ;1k stack
stack_ptr       dd      0               ;pointer to top of stack
ds_val          dw      0               ;default DS
break_handler   dd      0               ;storage for break handler
real_1b         dd      0               ;real mode int 1bh vector
real_23         dd      0               ;real mode int 23h vector
break_stat      db      0               ;original break status
_BSS    ends

DGROUP  group _BSS

start32code
extrn __x386_stacklow:dword
_controlc_open:

        cmp     real_1b,0
        jne short controlc_ret          ;jmp if already opened
        push    es
        pushad

        mov     ax,2509h
        int     21h
        mov     data_16_alias,ax

        mov     bh,5
        call    lock_mem                ;lock all touched memory
        mov     ds_val,ds               ;save default ds
        mov     stack_ptr,offset DGROUP:stack_ptr       ;starting esp
        mov     ax,3300h                ;get break status in dl
        int     21h
        mov     break_stat,dl           ;save original break status
        mov     ax,3301h
        mov     dl,al
        int     21h                     ;turn break status on
        mov     ax,2503h                ;get real mode int vector
        mov     cl,1bh
        int     21h
        mov     real_1b,ebx
        mov     cl,23h
        int     21h
        mov     real_23,ebx             ;save original real mode vectors
        mov     ax,250dh                ;get real mode interface addresses
        int     21h
        mov     es,data_16_alias
assume es:__X386_GROUP_16
        mov     es:real_to_prot_call,eax        ;save real mode callback address        mov     ebx,dword ptr es:real_handler_addr
        mov     ebx,dword ptr es:real_handler_addr
        mov     ax,2505h
        mov     cl,1bh
        int     21h
        mov     cl,23h
        int     21h                             ;hook real mode int 1bh and 23h
assume es:nothing
        popad
        pop     es
controlc_ret:
        ret

_controlc_close:
        cmp     real_1b,0
        je      controlc_ret            ;jmp if it was never opened

        push    es
        pushad
        mov     bh,6
        call    lock_mem                ;unlock the memory
        mov     ax,2505h                ;restore real mode int vectors
        mov     cl,1bh
        mov     ebx,real_1b
        int     21h
        mov     cl,23h
        mov     ebx,real_23             ;restore original int vectors
        int     21h
        xor     ebx,ebx
        mov     real_1b,ebx
        popad
        pop     es
        ret

prot_handler:
        pushad
        mov     eax,ss
        mov     ebx,esp
        lss     esp,fword ptr cs:stack_ptr      ;switch to new stack
        push    eax
        push    ebx                     ;save old stack pointer
        push    __x386_stacklow         ;save original stack limit
        mov     __x386_stacklow, offset DGROUP:stack_buf
;The above instruction adjusts the variable for detecting stack overflow.
        call    __controlc_handler
        pop     __x386_stacklow         ;restore stack limit
        lss     esp,ss:[esp]            ;load old stack pointer
        popad
        retf

lock_mem:       ;call with bl = 5 to lock, 6 to unlock memory
        push    ds
        pop     es
        mov     ecx,offset prot_handler
        mov     edx,offset lock_mem
        sub     edx,ecx                 ;calculate size to lock
        mov     ax,252bh
        mov     bl,1
        int     21h
        mov     ecx,offset DGROUP:__controlc_handler
        mov     edx,4
        int     21h
        mov     ecx,offset DGROUP:stack_buf
        mov     edx,1032
        int     21h
        ret
end32code

start16data     ;This is a real mode 16 bit segment
assume cs:__X386_GROUP_16
real_to_prot_call       dd      0
real_handler_addr       dw      offset real_handler
                        dw      __X386_GROUP_16
real_handler:                   ;This is the real mode entry point
        db      66h
        push    0               ;far pointer to selector structure
        push    0               ;dummy CS
;masm can't seem to be convinced to push a 32 bit offset so:
        db      66h
        db      68h                     ;push offset prot_handler
        dd      offset  _TEXT:prot_handler
        call    cs:real_to_prot_call    ;call the protected mode handler
        add     sp,10                   ;pop garbage
        iret

end16data
end
