include mac32.asm

comment &
        This example demonstrates how to use the mouse function 
        __x386_init_mouse which can be found in funcs32.asm.  This example 
        turns on the mouse and displays a character from A - Z incrementing 
        the character for each event from the mouse.  Strike any key to 
        terminate the program.  The details of the code in funcs32.asm 
        demonstrates how to call real mode procedures, and how to use real 
        mode call backs which enable real mode procedures to call protected 
        mode procedures. 
&

start32data

counter1        db      0

counter2        db      'A'

msg_suc         db      'Successful',24h

msg_fail        db      'Failure',24h

end32data

start32code
extrn __x386_mouse_init:near,__x386_mouse_term:near,__x386_memlock:near

public _asm_main
_asm_main   proc    near
;first lock the code and data for the mouse isr
        mov     eax,offset isr_ret[1]   ;offset of last instruction in isr
        sub     eax,offset mouse_isr    ;calculate length of isr
        push    eax
        push    cs
        push    offset mouse_isr
        call    __x386_memlock          ;lock the code
        lea     esp,[esp+12]            ;pop the parameters
        push    2                       ;length of data to be accessed
        push    ds
        push    offset DGROUP:counter1
        call    __x386_memlock          ;lock the data
        lea     esp,[esp+12]            ;pop the parameters
        push    0ffffh                  ;mask, call for any event
;see __x386_mouse_init in funcs32.asm, it locks the stack which is passed to 
;mouse_isr.
        push    offset mouse_isr        ;function to call
        call    __x386_mouse_init
        or      eax,eax
        jz short exit_err

loop1:
;check if keyboard has been hit
        mov     ah,11h
        int     16h                     ;BIOS check for keyboard input
;zero flag = 0 if keyboard has been hit, 1 if no input
        jnz     exit_loop               ;jmp if zero flag = 0
        cmp     counter1,0              ;check if mouse has been called
        je      loop1
;the mouse has called mous_isr, output a character
        mov     counter1,0
        mov     al,counter2             ;character to output
        mov     ah,9
        mov     bx,14                   ;page 0, attribute 14, yellow
        mov     cx,1                    ;output one character
        int     10h                     ;BIOS video IO
        jmp     loop1

exit_loop:
;keyboard has been hit, terminate the program
        call    __x386_mouse_term
        mov     edx,offset DGROUP:msg_suc
p_msg:
        mov     ah,9
        int     21h
        mov     ax,4c00h
        int     21h
exit_err:
        mov     edx,offset DGROUP:msg_fail
        jmp     p_msg
_asm_main   endp

comment &
        This function has the prototype: void mouse_isr(int mask, int state, 
        int posx, int posy).  This is called by the mouse driver through 
        mous_call, DOS32 and mous_call32.  See these functions in the file 
        funcs32.asm.

        The function below increments the variables counter1 and counter2 and 
        compares counter2 to "Z" and resets it to "A" if it is greater than Z. 
&
mouse_isr       proc    near
        inc     counter1
        inc     counter2
        cmp     counter2,'Z'
        jbe short isr_ret
        mov     counter2,'A'
isr_ret::
        ret
mouse_isr       endp

end32code
end
