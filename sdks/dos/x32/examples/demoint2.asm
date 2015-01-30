include mac32.asm

comment &
        This example demonstrates hooking both the protected and real mode 
        interrupt.

        The interrupt handler demonstrates how to read parameters from the 
        interrupt structure and alter the return location if desired.
&

start32data

        rm_vector       dd      ?       ;storage for real mode vector

        msg_suc         db      10,13,'Success',24h

        msg_fail        db      10,13,'Failure',24h

end32data

start32code
public _asm_main
_asm_main   proc    near
        mov     ax,2503h                        ;get real mode vector
        mov     cl,0ffh
        int     21h
        mov     rm_vector,ebx                   ;save vector

        mov     esi,ds                          ;save ds
        mov     eax,cs
        mov     ds,eax

        mov     edx,offset handler              ;ds:edx points to handler
        mov     ax,2506H                        ;hook real and protected modes
        mov     cl,0ffh                         ;hook interrupt 0ffh
        int     21h
        mov     ds,esi                          ;restore ds
;the interrupt 0ffh handler is now the "handler" procedure below

        int     0ffh                            ;should return to intff_ret
;if execution reaches this point, we have an error
        mov     edx,offset DGROUP:msg_fail      ;failure message
p_msg:
        mov     ah,9
        int     21h                             ;output message to screen

        mov     ebx,rm_vector
        mov     ax,2505h                        ;set real mode vector
        mov     cl,0ffh
        int     21h                             ;restore the real mode vector

        mov     ax,4c00h
        int     21h                             ;terminate the program

intff_ret::     ;point for interrupt handler to return to
        mov     edx,offset DGROUP:msg_suc       ;success message
        jmp     p_msg

_asm_main   endp

comment &
        This interrupt handler trashes ebp and eax.  It checks the interrupt 
        structure to determine if the interrupt originated in real or 
        protected mode, if it originated in protected mode, the CS value is 
        checked to see if the point of origin was within DOS32 or within the 
        32 bit application.  If it originates in the 32 bit application, the 
        eip value in the interrupt structure is altered to cause control to 
        return to intff_ret. 
&
handler proc    near                            ;handler for int ffh
        mov     ebp,ss:[esp+12]                 ;pointer to interrupt structure
        bt      word ptr ss:[ebp+14],1          ;check mode for real bit set
        jc short handler_ret                    ;jump if origin was real mode
        mov     eax,cs
        cmp     ax,ss:[ebp+20]                  ;check if cs = application cs
        jne short handler_ret
;alter return EIP in structure to cause execution to return to intff_ret
        mov     dword ptr ss:[ebp+16],offset intff_ret
handler_ret:
        iretd                                   ;return to caller
handler endp
end32code
end
