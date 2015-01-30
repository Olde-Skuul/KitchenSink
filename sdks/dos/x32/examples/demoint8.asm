comment &
        This program demonstrates hooking a hardware interrupt from assembly 
        language including locking of the affected memory.

        This also demonstates a protected mode handler which branches to the 
        original handler.
&

include mac32.asm

start32data

int8_vector     dd      ?       ;storage for protected mode offset
                dd      ?       ;storage for protected mode cs value
                dd      ?       ;storage for real mode vector

mem_lock_start  label   byte
ds_val          dw      ?       ;storage for default ds selector
counter         db      0       ;counts number of interrupts executed
mem_lock_size   equ     $ - mem_lock_start

msg_fail        db      10,13,'failure',24h

msg_success     db      10,13,'success',24h

end32data

start32code

public _asm_main
_asm_main   proc    near
comment &
        First we must lock the memory which is touched by the interrupt 
        handler.  This includes all code, data and stack which the handler 
        will read or write from.  In this case, the handler operates only on 
        the stack provided by DOS32 which is locked by DOS32 so we only need 
        to lock code and data.
&

        mov     ds_val,ds               ;save default ds for handler
        mov     ecx,offset DGROUP:int_handler
        push    cs
        pop     es                              ;es:ecx points to code
        mov     edx,offset DGROUP:dummy
        sub     edx,offset DGROUP:int_handler   ;number of bytes to lock
        mov     ax,252bh
        mov     bx,501h                 ;lock memory
        int     21h
        jc      error                   ;jump if lock fails
        push    ds
        pop     es                      ;Lock a DGROUP (in DS) memory area.
        mov     ecx,offset DGROUP:mem_lock_start
        mov     edx,mem_lock_size       ;The memory size to lock
        int     21h
        jc      error                   ;jump if lock fails

        mov     ax,2502h                ;get protected mode vector
        mov     cl,8                    ;timer tick interrupt
        int     21h
        mov     int8_vector[0],ebx      ;protected mode vector
        mov     int8_vector[4],es
        mov     ax,2503h                ;get real mode vector
        int     21h
        mov     int8_vector[8],ebx      ;real mode vector
        mov     ax,2506h                ;hook protected and real interrupts
        push    ds                      ;save ds
        push    cs
        pop     ds                      ;ds = cs value
        mov     edx,offset int_handler  ;edx = eip value
        int     21h
        pop     ds                      ;restore ds
test_loop:
        cmp     counter,100             ;check if 100 interrupts executed
        jb      test_loop
;the above loop should take about 5 seconds to complete
        mov     ebx,int8_vector[8]
        push    ds
        lds     edx,fword ptr int8_vector[0]
        mov     cl,8
        mov     ax,2507h                ;set protected and real vectors
        int     21h                     ;restore int 8 to original handler
        pop     ds

        cmp     counter,100
        jb short error
        mov     edx,offset DGROUP:msg_success

print_msg:
        mov     ah,9
        int     21h

        xor     eax,eax
        ret

error:
        mov     edx,offset DGROUP:msg_fail
        jmp     print_msg

_asm_main   endp

comment &
        The handler below is called for all timer ticks, both real and 
        protected mode origin.  All registers must be preserved and all 
        registers including DS should be considered to be unknown upon entry.

        CS can be used to read data in the data segment but cannot be used to 
        write to memory, thus we must load the default DS to increment 
        counter. 
&

int_handler     proc    near
        push    ds                              ;save ds
        mov     ds,cs:ds_val                    ;use cs to load ds
        inc     counter
        pop     ds
        jmp     fword ptr cs:int8_vector        ;jump to original handler
int_handler     endp

dummy   proc    near            ;dummy label
dummy   endp

end32code
end
