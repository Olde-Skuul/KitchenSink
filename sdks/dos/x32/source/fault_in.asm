;fault_in.asm
;Copyright FlashTek Inc. 1993.

include mac32.asm

start32data
func_ptr        dd      ?               ;point to user defined function
stack_ptr       dd      ?               ;offset of stack
                dw      ?               ;default ss
ds_val          dw      ?               ;default ds
end32data

start32code
comment &
        #include <x32.h>
        void _cdecl _x32_fault_intercept(void (* _cdecl func) ( struct FAULT_STRUC *fault))

        func is a user defined function which receives control when there is 
        some type of fault.  If func returns, the program will be terminated 
        without a register dump.  func is passed a pointer to a structure 
        which indicates the processor state at the time of fault as follows: 

        struct FAULT_STRUC
        {
          unsigned eax,ebx,ecx,edx,esi,edi,ebp;
          unsigned short ds,es,fs,gs,
          fault_num,            /* fault number                         */
          mode;                 /* indicates real or protected mode     */
          unsigned eip;
          unsigned short cs,space    /* space is to maintain dword alignment */
          unsigned eflags,esp;
          unsigned short ss;
        }

        Fault numbers are as follows:

        0       divide by 0
        6       invalid op code
        9       coprocessor segment overrun
        10      invalid TSS
        11      segment not present
        12      stack fault
        13      general protection fault
        14      page fault

        When the user supplied fault handler receives control, the stack will 
        be reset to approximately the size it was at the time main() was 
        called and all variables allocated on the stack previous to the fault 
        will be undefined.  Execution can continue indefinitely in the new 
        thread of execution with no need to return.  There is no limit to the 
        number of faults which can occur.  There is also no need to unhook any 
        exceptions prior to termination.
&
public __x32_fault_intercept
__x32_fault_intercept   proc    near
        mov     eax,ss:[esp+4]                  ;pointer to function
        mov     func_ptr,eax                    ;save pointer
        mov     eax,ebp
;unwind the stack to find the original ebp
loop1:
        mov     ecx,eax                         ;save old value
        mov     eax,[eax]
        or      eax,eax
        jnz     loop1
;ecx now points to a zero on the stack where the original ebp exists
        mov     stack_ptr,ecx
        mov     word ptr stack_ptr[4],ss
        mov     ds_val,ds
        push    ds
        push    cs
        pop     ds
        mov     edx,offset fault_han
        mov     ax,2533h                ;set exception handler vector
        mov     cl,0
        int     21h
        mov     cl,6
        int     21h
        mov     cl,9
        int     21h
        mov     cl,10
        int     21h
        mov     cl,11
        int     21h
        mov     cl,12
        int     21h
        mov     cl,13
        int     21h
        mov     cl,14
        int     21h
        pop     ds
        ret


fault_han:              ;X-32 transfers control here when an exception occurs
        sti
        cld             ;set the flags as they should be
        add     esp,12  ;pop iretd structure
        pop     esp     ;pop the int_struc pointer
        add     esp,4   ;pop eax from int_struc
        push    ebp
        push    edi
        push    esi
        push    edx
        push    ecx
        push    ebx
        push    eax             ;fault_structure is now complete
        mov     esi,esp         ;save pointer to structure
        push    ss
        pop     ds              ;ds:esi points to structure
        lss     esp,fword ptr cs:stack_ptr
        mov     ebp,esp         ;make ebp point to zero
        mov     es,cs:ds_val
        sub     esp,60          ;make room for fault_structure
        mov     edi,esp
        mov     ecx,60/4
        rep     movsd           ;mov 60 bytes
        mov     ds,cs:ds_val
        mov     ax,2501h
        int     21h             ;reset X-32 stack
        push    esp             ;pointer to fault_structure
        call    func_ptr
        mov     ax,4c01h
        int     21h             ;terminate program

__x32_fault_intercept   endp
end32code
end

