include mac32.asm
comment &
        This program demonstrates how to allocate static real mode memory, and 
        access it both from real mode code and 32 bit protected mode code.  
        The function main places the number 12345678h in the real mode array 
        "real_data".  main then calls the real mode function "real_proc" which 
        retrieves that number and returns to protected mode with that number 
        in EAX.  main then causes a general protection fault so that the 
        registers can be examined.
&
 
start16code             ;define start of real mode code segment
 
real_data       db      20000 dup (0)   ;real mode data

real_proc       proc    far             ;procedure to call from prot mode
assume ds:__X386_CODESEG_16             ;name of real mode code segment
        mov     eax,dword ptr DS:real_data[10000] ;mov the dummy data into eax
        retf
real_proc       endp
 
end16code               ;end of real mode code segment
 
start32data             ;protected mode data segment
        extrn __x386_zero_base_selector:word    ;data selector
end32data
 
start32code                 ;protected mode code segment
public _asm_main
_asm_main   proc    near
        mov     ax,2509h                ;get system segments and selectors
        int     21h                     ;get real mode segment in bx
;There are no fixups done on 32 bit code so you cannot use segment names as
;immediate values, you must use function 2509h.  This function destroys all 
;registers, filling each 32 bit register with two segments or two selectors.

        push    ebx                     ;save real mode segment which is in bx
        mov     es,__x386_zero_base_selector
;note that the above selector is not hardwired but is available through the
;public variable as shown above, it has a base of zero, 4 gbyte limit

        movzx   ebx,bx                  ;zero upper word
        shl     ebx,4                   ;convert segment to absolute address
assume es:nothing
        mov     dword ptr es:real_data[ebx+10000],12345678h
;above instruction puts dummy data in real_data[10000], the selector in es 
;points to zero, ebx gives the offset of the start of the real mode segment
;be careful that es does not have any assumes on it

        pop     ebx                     ;restore real mode segment in bx
        rol     ebx,16
        mov     bx,offset real_proc     ;ebx now = cs:ip of real_proc
        xor     ecx,ecx                 ;copy zero parameters on stack
        mov     ax,250eh
        int     21h                     ;call real_proc

;make a general protection fault to examine registers.
        push    cs
        pop     ss
;illegal value in ss will terminate program and dump registers to screen.
;eax should have 12345678h

_asm_main   endp
end32code
end


