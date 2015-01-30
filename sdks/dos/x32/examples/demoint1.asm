include mac32.asm

comment &
        This example demonstrates hooking a protected mode interrupt without 
        hooking the real mode interrupt.  The interrupt handler returns a 
        pointer in edx which is used to print a message.  This program also 
        demonstrates that protected mode interrupts do not need to be restored 
        prior to terminating the program.  Only real mode interrupts need be 
        restored. 
&

start32data

        msg_suc         db      10,13,'Success',24h

        msg_fail        db      10,13,'Failure',24h

end32data

start32code
public _asm_main
_asm_main   proc    near
        push    ds                              ;save ds
        push    cs
        pop     ds                              ;mov ds,cs
        mov     edx,offset handler              ;ds:edx points to handler
        mov     ax,2504H                        ;set protected mode vector
        mov     cl,99h                          ;set interrupt 99h
        int     21h
        pop     ds                              ;restore ds
;the interrupt 99h handler is now the "handler" procedure below

        mov     edx,offset DGROUP:msg_fail      ;default pointer
        int     99h                             ;handler should alter edx
        mov     ah,9
        int     21h                             ;output message to screen

        mov     ax,4c00h
        int     21h                             ;terminate the program

_asm_main   endp

handler proc    near                            ;handler for int 99h
        mov     edx,offset DGROUP:msg_suc       ;change message to success
        iretd                                   ;return to caller
handler endp
end32code
end
