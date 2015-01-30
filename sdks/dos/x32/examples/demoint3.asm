include mac32.asm

comment &
        This example demonstrates hooking a protected mode interrupt and 
        routing it through a handler which changes stacks and calls a C 
        function.  This is required for most C compilers since most C 
        compilers expect the base address of SS to equal the base address of 
        DS. 
&

start32data

stack_ptr       dd      offset DGROUP:stack_space[1024] ;esp value
                dd      ?                               ;space for ss

int_stack_ptr   dd      ?               ;storage for int handler stack pointer
                dd      ?

stack_space     db      1024 dup (?)                    ;stack of 1024 bytes

        msg_suc         db      10,13,'Success',24h

        msg_fail        db      10,13,'Failure',24h

end32data

start32code
public _asm_main
_asm_main   proc    near
        mov     word ptr stack_ptr[4],ds        ;save ds
        push    cs
        pop     ds                              ;mov ds,cs
        mov     edx,offset handler              ;ds:edx points to handler
        mov     ax,2504H                        ;set protected mode vector
        mov     cl,99h                          ;set interrupt 99h
        int     21h
        mov     ds,word ptr cs:stack_ptr[4]     ;restore ds
;the interrupt 99h handler is now the "handler" procedure below
        int     99h

        mov     ax,4c00h
        int     21h                             ;terminate the program

_asm_main   endp

handler proc    near                            ;handler for int 99h
        push    ds
;we will initialize ds in case the caller was using something other than default
        mov     ds,word ptr cs:stack_ptr[4]     ;initialize ds
        mov     int_stack_ptr,esp               ;save original esp
        mov     word ptr int_stack_ptr[4],ss    ;save original ss
        lss     esp,fword ptr cs:stack_ptr      ;switch to new stack
        call    c_function
        lss     esp,fword ptr int_stack_ptr     ;restore original stack
        pop     ds                              ;restore original ds
        iretd                                   ;return to caller
handler endp

comment &
        This function can be any function written in C.  It recieves control 
        with ss = ds and can return with a near return instruction. 
&
c_function      proc    near
        mov     eax,ss
        mov     ecx,ds
        cmp     eax,ecx                         ;check if ds = cs
        jne short error
        mov     edx,offset DGROUP:msg_suc
p_msg:
        mov     ah,9
        int     21h
        ret                                     ;near return to caller

error:
        mov     edx,offset DGROUP:msg_fail
        jmp     p_msg

c_function      endp

end32code
end

