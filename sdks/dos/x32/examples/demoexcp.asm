include mac32.asm

comment &
        This example demonstrates hooking exception 13 which is the general 
        protection fault.  This provides applications with a more graceful 
        method of handling faults.
&

start32data
        stack_ptr       dd      ?               ;esp value
                        dd      ?               ;ss value

        ds_val          dw      ?               ;ds value

        msg_fail        db      10,13,'Failure',24h
        msg_suc         db      10,13,'Success',24h
end32data

start32code
public _asm_main
_asm_main       proc    near
        mov     ax,2533h                        ;set exception handler vector
        mov     cl,13                           ;general protection fault #
        mov     edx,offset fault_handler
        push    ds                              ;save ds
        push    cs
        pop     ds                              ;cs of fault_handler
        int     21h
        pop     ds
        mov     stack_ptr,esp
        mov     word ptr stack_ptr[4],ss        ;save stack pointer for handler
        mov     ds_val,ds                       ;save ds for handler

;Now we will create a general protection fault by attempting to write to the 
;code segment.
        mov     byte ptr cs:[0],1       ;cause a general protection fault
;execution should never reach this point
        mov     edx,offset DGROUP:msg_fail
        jmp     p_msg

_asm_main       endp


comment &
        This fault handler restores the stack to a legitimate stack and resets 
        the DOS32 system.  Execution can then continue indefinitely but must 
        never return on the stack frame received by this handler.
&
fault_handler   proc    near
        mov     ds,cs:ds_val                    ;restore ds
        lss     esp,fword ptr stack_ptr         ;restore stack
        mov     ax,2501h
        int     21h                             ;reset DOS32
comment &
        Execution could now branch to other code and continue running.  For 
        the purpose of this demonstration, we will terminate the program now.
&

        mov     edx,offset DGROUP:msg_suc
p_msg:: mov     ah,9
        int     21h
        mov     ax,4c00h                        ;terminate program
        int     21h

fault_handler   endp

end32code
end
