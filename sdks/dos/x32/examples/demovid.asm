include mac32.asm
comment &
        This code demonstrates various methods which can be used to access the 
        video buffer directly.
&
start32data
extrn __x386_zero_base_selector:word,__x386_zero_base_ptr:dword
end32data

start32code
extrn __x386_mk_protected_ptr:dword

public _asm_main
_asm_main   proc    near
comment &
        This example shows how to allocate a new selector with a base address 
        which will point to B8000H which is the video buffer for a color 
        monitor.  This calls a function which should return a far pointer in 
        dx:eax.  If a selector was successfully allocated, the offset in eax 
        will equal zero.  If not, eax will = the requested address and dx will 
        equal __x386_zero_base_selector.
&
        push    0b8000h
        call    __x386_mk_protected_ptr         ;returns pointer in dx:eax
        mov     es,dx                           ;this should be a video selector
        mov     byte ptr es:[0],'X'             ;place an X on screen



comment &
        This example writes to screen using a selector which has an address of 
        absolute zero.  This selector is stored in a global variable and is 
        available for applications to use in whatever manner they choose.
&
        mov     es,__x386_zero_base_selector    ;load the selector
        mov     byte ptr es:[0b8002H],'Y'       ;place a Y on screen



comment &
        This example writes to screen using near pointers based on the default 
        selector normally found in DS.  The segment limits DOS32 sets on DS 
        allow the use of negative offsets.  The offset which effectively 
        points to absolute zero is stored in the global variable 
        __x386_zero_base_ptr.
&
        mov     eax,__x386_zero_base_ptr        ;ds:eax points to zero
        mov     byte ptr ds:[eax + 0b8004H],'Z' ;place a Z on screen

        mov     ah,4ch
        int     21h                     ;terminate the program

_asm_main   endp
end32code
end
