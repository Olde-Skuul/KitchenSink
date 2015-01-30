include mac32.asm

comment &
        This example demonstrates accessing a Wietek abacus coprocessor chip.  
        This device requires access to a physical address which is not 
        normally mapped into the X32 memory space.
&

start32data

extrn __x386_zero_base_ptr:dword

msg_suc         db      10,13,'success',24h

msg_fail        db      10,13,'failure',24h

end32data

start32code
public _asm_main
_asm_main   proc    near
        push    64*1024                 ;size of Weitek address space
        push    0c0000000h              ;32 bit physcial address of Weitek chip
        call    _dos32_map_physical_address
        lea     esp,[esp+8]
        cmp     eax,-1
        je      error_w
        mov     ebx,eax

;Weitek chip detection code from "ABACUS software designer's guide" is below
        mov     eax,40000000h           ;2.0
        mov     ds:[ebx + 404h],eax     ;wfld ws1,eax
        mov     ds:[ebx + 408h],eax     ;wfld ws2,eax
        mov     ds:[ebx + 2809h],al     ;wfneg ws2,ws1
        or      eax,(1 shl 31)          ;negate eax
        mov     ebx,ds:[ebx + 808h]     ;wfst ebx,ws2
        cmp     eax,ebx                 ;eax = ebx if ABACUS is present
        mov     edx,offset DGROUP:msg_suc
        je short exit_w                 ;jmp if success
error_w:
        mov     edx,offset DGROUP:msg_fail
exit_w:
        mov     ah,9
        int     21h
        mov     ax,4c00h
        int     21h

_asm_main   endp


;;;;;;;;;;;;;;;;;;;;;;;;;
; Enables access to physical memory, used for memory mapped IO devices
; use: _dos32_map_physical_address(abs_addr, size)
; returns near pointer to device
; Region to be mapped must be completely above or completely below 1 meg
; Function fails if insufficient memory or if DPMI host refuses service
;;;;;;;;;;;;;;;;;;;;;;;;;
_dos32_map_physical_address     proc    near
        push    ebx
        mov     ebx,ss:[esp+8]          ;addr
        mov     ecx,ss:[esp+12]         ;size
        mov     eax,ebx
        add     eax,ecx                 ;eax now has top of address to be mapped
        jc short mp_err                 ;catch wrap around
        cmp     eax,1024*1024           ;check if top address is below 1 meg
        jbe short mp_1
;the top address is above 1 meg, the start address must be also or we have
;to fail the function call.
        cmp     ebx,1024*1024
        jb short mp_err
;entire address is above 1 meg
        mov     ax,350ah                ;map physical address
        int     21h
        jc short mp_err
        mov     eax,ebx                         ;absolute address
        add     eax,__x386_zero_base_ptr        ;convert to DGROUP relative addr
        pop     ebx
        ret
mp_err:                 ;carry flag will be set at this point
        pop     ebx
        sbb     eax,eax
        ret
mp_1:   ;entire requested space is below 1 megabyte
        mov     eax,__x386_zero_base_ptr
        add     eax,ebx                 ;construct a near pointer
        pop     ebx
        ret
_dos32_map_physical_address     endp

end32code
end

