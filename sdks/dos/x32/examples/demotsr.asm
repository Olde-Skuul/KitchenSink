comment &
        Demonstration program for a simple TSR.  This program intercepts 
        interrupt 5 which is the print screen interrupt and then Terminates 
        and Stays Resident forming a TSR.  Once the program is installed, 
        hitting the print screen key will cause the speaker to beep indicating 
        that the TSR is active.
&


include mac32.asm

comment &
        Include two of the variables from options.asm and set them to values 
        which reduce the conventional memory usage of X-32 to the minimum.  
        Read the comments in options.asm for a more complete description of 
        how these variables work.  This is not required for a TSR but it 
        reduces the amount of conventional memory consumed by the TSR to the 
        absolute minimum.  These variables must be defined in the segment as 
        shown below and they must be declared public. 
&

__X386_DATASEG_16      segment para public 'DATA16'

public __x386_dos_buffer_size,__x386_conv_mem_resv

__x386_dos_buffer_size  dd      4096    ;minimum size DOS buffer
__x386_conv_mem_resv    db      255     ;reserve maximum memory for DOS

__X386_DATASEG_16       ends



start32code
public _asm_main
_asm_main   proc    near

        mov     cl,5                    ;intercept the print screen interrupt
        push    cs
        pop     ds                      ;load ds with cs
        mov     edx,offset handler      ;ds:edx is the vector of the handler
        mov     ax,2506h                ;hook real and protected mode interrupts
        int     21h
        mov     ax,3100h
        int     21h                     ;terminate and stay resident
;no return from the above int 21h

handler: ;this is where control transfers to when the print screen key is hit.
;this is an interrupt handler, no assumptions should be made about DS and SS!
        pushad                  ;save all registers
; Make a tone with the speaker to show the handler was called
        mov     al,10110110b    ;data for timer chip
        out     43h,al
        out     42h,al          ;garbage for least signifant byte
        mov     al,20
        out     42h,al          ;20 for most significant byte
        in      al,61h          ;save state of port 61h
        push    eax
        or      al,3
        out     61h,al
        pop     eax
        mov     ecx,300000
loop1:                  ;waste some time while the speaker is on
        mov     ebx,ebx
        loop    loop1
        out     61h,al          ;turn speaker off
        popad                   ;restore registers
        iretd                   ;return to caller

_asm_main   endp
end32code
end

