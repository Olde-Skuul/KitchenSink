include mac32.asm

ifdef MEMLOCK

start32data
extrn  __x386_zero_base_selector:word,__x386_zero_base_ptr:dword
extrn __x386_stacklow:dword
__x386_mk_protected_ptr         dd      offset  __x32_mk_protected_ptr
__x386_free_protected_ptr       dd      offset __x32_free_protected_ptr
__x386_get_abs_address          dd      offset __x32_get_abs_address
end32data

start32code
;;;;;;;;;;;;;;;;;;;;;;;;;
; Lock a region of memory in a virtual memory environment
; Use: _x386_memlock(far pointer, length)
; far pointer to start of region to lock
; Returns: 0 if success, -1 if failure
; May 26,1991
;;;;;;;;;;;;;;;;;;;;;;;;;
public __x386_memlock,__x32_memlock
__x386_memlock  label   near
__x32_memlock   proc    near
        mov     ax,501h         ;lock page, far pointer
mem_man_enter:                  ;entry point for other mem management functions
        push    ebp
        mov     ebp,esp
        push    ebx
        mov     ebx,eax                         ;proper value of bx was in ax
        mov     ax,252bh
        mov     edx,[16+ebp]                    ;length in bytes
        les     ecx,[8+ebp]                     ;es:ecx points to start
        int     21h
        sbb     eax,eax
        pop     ebx
        pop     ebp
        push    ds
        pop     es              ;restore es in case of non standard far pointer
        ret
__x32_memlock   endp

;;;;;;;;;;;;;;;;;;;;;;;;;
; Unlock a region of memory for paging in a virtual memory environment
; Use: _x386_memunlock(far pointer, length)
; far pointer to start of region to unlock
; Returns: 0 if success, -1 if failure
; May 26,1991
;;;;;;;;;;;;;;;;;;;;;;;;;
public __x386_memunlock,__x32_memunlock
__x386_memunlock        label   near
__x32_memunlock         proc    near
        mov     ax,601h
        jmp short mem_man_enter
__x32_memunlock         endp


;;;;;;;;;;;;;;;;;;;;;;;;;
; Creates a protected mode selector
; Use: _x386_mk_protected_ptr(address)
; Selector will be read/write with a base address = address and a 4 gbyte limit
; Returns: far pointer with 0 for offset if success
; if failure: address for offset and __x386_zero_base_selector for the 
; selector.
; Oct 27,1991
;;;;;;;;;;;;;;;;;;;;;;;;;
public __x386_mk_protected_ptr,__x32_mk_protected_ptr
__x32_mk_protected_ptr  proc    near
        push    ebp
        mov     ebp,esp
        push    ebx
        mov     ecx,ss:[ebp + 8]        ;get address in ecx
        mov     ax,3501h                ;allocate selector
        int     21h                     ;returns selector in BX
        jc short mk_ptr_1
        mov     al,3                    ;set selector base address
        int     21h                     ;selector in BX, address in ECX
        mov     ecx,-1                  ;set limit to max
        mov     al,5                    ;set limit of selector in BX
        jc short mk_ptr_3               ;jmp if error
        int     21h
        jc short mk_ptr_3               ;jmp if error
        xor     eax,eax
        movzx   edx,bx
mk_ptr_2:
        pop     ebx
        pop     ebp
        ret

mk_ptr_3:       ;error after allocation
        mov     ax,3502h
        int     21h                     ;deallocate selector
mk_ptr_1:       ;error during allocation
        mov     eax,ecx                 ;address
        mov     dx,__x386_zero_base_selector
        jmp short mk_ptr_2

__x32_mk_protected_ptr  endp

;;;;;;;;;;;;;;;;;;;;;;;;;
; Frees a protected mode selector
; Use: _x386_free_protected_ptr(far pointer)
; Selector will be freed if previosly allocated
; Returns: 0 if success, -1 if invalid selector
; Oct 27,1991
;;;;;;;;;;;;;;;;;;;;;;;;;
public __x386_free_protected_ptr,__x32_free_protected_ptr
__x32_free_protected_ptr        proc    near
        push    ebx
        mov     ebx,ss:[esp + 12]
        cmp     bx,__x386_zero_base_selector
        stc                             ;for sbb at free_ptr_1
        je short free_ptr_1             ;don't deallocate zero_base_selector
;must load zero in es, fs, and gs if they contain the selector in bx.
        mov     eax,es
        cmp     ax,bx
        je short zero_es
z_es:
        mov     eax,fs
        cmp     ax,bx
        je short zero_fs
z_fs:
        mov     eax,gs
        cmp     ax,bx
        je short zero_gs
z_gs:
        mov     ax,3502h                ;deallocate selector
        int     21h
free_ptr_1:
        sbb     eax,eax
        pop     ebx
        ret
zero_es:
        push    0
        pop     es
        jmp     z_es
zero_fs:
        push    0
        pop     fs
        jmp     z_fs
zero_gs:
        push    0
        pop     gs
        jmp     z_gs

__x32_free_protected_ptr        endp

;;;;;;;;;;;;;;;;;;;;;;;;;
; Determines the absolute address of a far pointer
; Use: _x386_get_abs_address(far pointer)
; Returns: address if success, -1 if invalid selector
; Oct 27,1991
;;;;;;;;;;;;;;;;;;;;;;;;;
public __x386_get_abs_address,__x32_get_abs_address
__x32_get_abs_address   proc    near
        push    ebx
        mov     ebx,ss:[esp + 12]       ;selector
        mov     ax,3504h                ;get address of selector in bx
        int     21h                     ;returns address in ecx
        pop     ebx
        jc short get_addr_1
        add     ecx,ss:[esp + 4]        ;offset from far pointer
        mov     eax,ecx
        ret
get_addr_1:
        sbb     eax,eax
        ret
__x32_get_abs_address   endp

;;;;;;;;;;;;;;;;;;;;;;;;;
; Enables access to physical memory, used for memory mapped IO devices
; use: __x386_map_physical_address(abs_addr, size)
; returns near pointer to device
; Region to be mapped must be completely above or completely below 1 meg
; Function fails if insufficient memory or if DPMI host refuses service
;;;;;;;;;;;;;;;;;;;;;;;;;
public __x386_map_physical_address,__x32_map_physical_address
__x32_map_physical_address      label   near
__x386_map_physical_address     proc    near
        push    ebx
        mov     ebx,ss:[esp+8]          ;addr
        mov     ecx,ss:[esp+12]         ;size
        mov     eax,ebx
        add     eax,ecx                 ;EAX now has top of address to be mapped
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
__x386_map_physical_address     endp

;;;;;;;;;;;;;;;;;;;;;;;;;
; Identical to __x386_map_physical_address except on 486 machines or above, it
; enables the on chip cache memory for the mapped in memory space.  The 
; function above disables the cache memory for the mapped in device for 
; compatibility with things like the Weitek coprocessor and other devices for 
; which caching would cause problems.  This function does nothing under DPMI 
; systems because caching is controlled purely by the host and is beyond the 
; control of X-32. 
; use: __x386_map_physical_add_fast(abs_addr, size)
; returns near pointer to device
; Region to be mapped must be completely above or completely below 1 meg
; Function fails if insufficient memory or if DPMI host refuses service
;;;;;;;;;;;;;;;;;;;;;;;;;
public __x386_map_physical_add_fast,__x32_map_physical_add_fast
__x32_map_physical_add_fast      label   near
__x386_map_physical_add_fast     proc    near
        mov     eax,cs
        cmp     ax,2bh
        jne     __x386_map_physical_address     ;jmp if DPMI
        push dword ptr ss:[esp+8]
        push dword ptr ss:[esp+8]               ;push parameters for function
        call    __x386_map_physical_address
        pop     edx                             ;abs_addr
        pop     ecx                             ;size in bytes
        cmp     eax,-1
        je short add_fast_ret                   ;jmp if mapping failed
        add     ecx,0fffh
        shr     ecx,12                  ;calculate number of page table entries
        mov     edx,eax                 ;near pointer to mapped device
        sub     edx,__x386_zero_base_ptr        ;calculate absolute address
        shr     edx,10                  ;divide by 1k
        and     dl,0fch                 ;round down to nearest 4 byte boundary
;edx is now an index into the page table.
        add     edx,400000h
;edx is now an absolute pointer to the page table
        add     edx,__x386_zero_base_ptr
;edx is now a near pointer to the page table
add_fast_loop:
        and byte ptr ds:[edx],0efh      ;zero the PCD (page cache disable) bit
        add     edx,4
        loop    add_fast_loop
add_fast_ret:
        ret
__x386_map_physical_add_fast     endp

end32code

endif   ;MEMLOCK

ifdef I387
     comment&
        This code is required for the Watcom 387 emulation code.  It is pulled 
        in due to the publics __init_387_emulator and __fini_387_emulator.  
        This code must be in a library which is searched prior to emu387.lib.
&

start32code

if @version LT 600
assume cs:_TEXT
endif

assume ds:_TEXT

public __fini_387_emulator,__init_387_emulator
extrn __sys_fini_387_emulator:near,__sys_init_387_emulator:near
extrn __int7:near,__int7_pl3:near,__x386_zero_base_ptr:dword
extrn __x386_zero_base_selector:word,__X32VM:byte


error2:         ;not 9.0 emulator, check if 9.5 or 9.5a emulator
        cmp     eax,offset __int7[-24h]
        jne short init_387_1            ;jmp if 9.5b or above emulator
comment &
        The 9.5A and below emulators require the patch, emulators from 9.5b 
        and up do not require them.  First we check for DPMI, if not DPMI, we 
        will allow the emulator to hook the IDT directly. 
&
        push    eax
        mov     eax,cs
        cmp     al,2bh          ;apps never have gdt selectors under DPMI
        pop     eax
        jne short init_387_dpmi ;jmp if DPMI
init_387_1:
        pop     es
        pop     ebx
        pop     eax
        jmp     __sys_init_387_emulator

init_387_dpmi:
        mov     __X32VM,0               ;do not use direct hook method
        add     ebx,2bh                 ;adjust offset of location to fix
        push    ebx
        mov     ebx,offset int7_call[1]
        sub     ebx,__x386_zero_base_ptr
        sub     dword ptr es:[ebx],5    ;adjust destination call
        pop     ebx
        jmp short error2_ret

__init_387_emulator:
comment &
        We will check at location __sys_init_387_emulator[111] for the address 
        of int7_pl3.  If this is not equal, we are not working with Version 
        9.0 of the emulator.  We also check the relative offset between 
        int7_pl3 and int7.  The difference between these locations should be 
        21h if we are working with 9.0.
&
        push    eax
        push    ebx
        push    es
        mov     es,__x386_zero_base_selector
        mov     eax,offset __int7_pl3
        cmp     eax,offset __int7[-21h]
;load location of int 7 vector in code segment
        mov     ebx,offset __sys_init_387_emulator[111h]
        jne short error2                        ;jmp if not 9.0 emulator
error2_ret:
        sub     ebx,__x386_zero_base_ptr        ;es:ebx points to vector
        cmp     eax,es:[ebx]
        jne short skip_patch
comment&
        The emulation code will now be assumed to be correct.  We will insert 
        the address of int7_patch into the location in the code for the int 7 
        vector.
&
        mov     dword ptr es:[ebx],offset int7_patch
skip_patch:
        pop     es
        pop     ebx
        pop     eax
        jmp     __sys_init_387_emulator

comment&
        The code below replaces the code at int7_pl3 and serves to provide the 
        interface between the 387 emulation services and the X-32 interrupt 
        structure which is not identical to the structure passed to interrupt 
        handlers under Pharlap.  The code below must call __int7[33] after 
        arranging the stack as follows: 

        CS
        EIP             +34h    ;origin of interrupt and return address
        xxxxxxxxx
        pushad structure with esp from int_struc
                ES   +4
        SS      DS   <------- ss:esp

        We must restore registers as per the popad structure since the 
        emulator may choose to alter them, for example, when storing the 
        status word to ax. 
&
int7_patch      proc    near
        sti
        mov     eax,ss:[esp+12]         ;pointer to int_struc
        push    dword ptr ss:[eax+20]   ;cs at origin
        push    dword ptr ss:[eax+16]   ;eip at origin
        push    eax                     ;int_struc pointer
        push    eax
        push    eax
        pushad
        mov     ecx,ss:[eax+28]         ;esp from int_struc
        mov     ss:[esp+12],ecx         ;place esp in pushad structure
        push    es
        push    word ptr ss:[eax+32]    ;push ss
        db      66h
        push    ds                      ;push word ds on stack
        mov     eax,ss:[eax]            ;original eax value
        mov     ss:[esp+24h],eax        ;restore original eax in pushad struc
int7_call:
        call    __int7[33]
        pop     ds
        pop     es
comment&
        We must now deal with a 386 bug regarding popad and esp.  The popad 
        instruction is not supposed to modify esp, however when we do a popad 
        in a 32 bit code segment with a 16 bit stack segment, the high word of 
        esp will be set to the value in the popad structure.  Thus we must set 
        that high word to zero in case we are running on a 16 bit stack which 
        is typically the case under X-32 interrupt handlers.
&
        xor     eax,eax
        mov     ss:[esp+12],eax         ;zero esp in the popad structure
        popad
        xchg    eax,ss:[esp]            ;load pointer to int_struc
        pop     dword ptr ss:[eax]      ;save return ebp
        add     esp,8
        pop     dword ptr ss:[eax+16]   ;set new eip
        add     esp,4                   ;pop CS value
        mov     eax,ss:[eax]            ;restore eax
        iretd
int7_patch      endp

__fini_387_emulator:    ;for Watcom 9.5B, we must set __X32VM = 0
        push    dword ptr __X32VM               ;save old value
        mov     __X32VM,0
        call     __sys_fini_387_emulator
        pop     dword ptr __X32VM               ;restore original value
        ret
end32code

XI      segment word use32 public 'DATA'
db      0,1
dd      offset _TEXT:__init_387_emulator
XI      ends

YI      segment word use32 public 'DATA'
db      0,1
dd      offset _TEXT:__fini_387_emulator
YI      ends

DGROUP  group _TEXT,XI,YI,_DATA
endif   ;I387

ifdef MOUSE

start32data

extrn __x386_zero_base_selector:word

cfuncstack      db      1024 dup (0)            ;1 kbyte stack for C function

stack_ptr       dd      offset DGROUP:stack_ptr[-4]     ;esp value
                dd      ?                               ;ss value

cfuncaddr       dd      ?                       ;storage for pointer to function

end32data

start32code

comment&
        The function below can be called from C and has the prototype:
        int __x32_mouse_init(*func(int mask, int state, int posx, int 
        posy),mask), where mask is the bit mask to be passed to the mouse 
        driver indicating what conditions the driver should call the 
        signaling function.  The mask passed to the func indicates which 
        event caused the function to be called.  State indicates the button 
        state as passed from the driver in bx, posx and posy are the x,y 
        coordinates of the cursor which the driver returns in cx:dx Returns 0 
        if failed, non zero if success.

        format of the mask:

        Bit 0  x or y coordinate has changed
        Bit 1  left button was depressed
        Bit 2  left button was released
        Bit 3  right button was depressed
        Bit 4  right button was released
        Bit 5  middle button was depressed
        Bit 6  middle button was released
        Other bits are undefined.

&
public __x386_mouse_init,__x32_mouse_init
__x32_mouse_init        label   near
__x386_mouse_init       proc    near
        xor     eax,eax
        mov     es,__x386_zero_base_selector
        cmp     ax,es:[33h*4+2]                 ;int 33h real mode cs
        je short init_ret                       ;jmp if selector is zero
        int     33h                             ;returns non zero if present
        or      eax,eax
        jz short init_ret
;mouse driver is present     
        push    ebp
        push    ebx
        push    esi
        push    edi                     ;save registers
;lock the code, data and stack
        mov     ax,252bh                ;VM management functions
        mov     bx,501h                 ;lock pages, es:ecx = absolute address
        mov     ecx,offset DGROUP:cfuncstack    ;start address of region to lock
        mov     edx,1036                        ;size of region to lock
        push    ds
        pop     es
        int     21h                             ;lock the stack and data
        jc short mous_err
        mov     ecx,offset DGROUP:mous_call32
        mov     edx,offset DGROUP:dummy
        sub     edx,ecx                         ;calculate size of code
        int     21h                             ;lock the code
        jc short mous_err
        mov     ecx,offset DGROUP:__x386_stacklow
        mov     edx,4                           ;lock 4 bytes
        int     21h
        jc short mous_err
;turn on the cursor
        mov     ax,1
        int     33h
;set up the call back address
        mov     ax,2509h                ;get system segments and selectors
        int     21h                     ;returns real mode code segment in bx
        shl     ebx,16                  ;mov cs to high word
        mov     bx,offset __X386_CODESEG_16:mouse_init
        push    ebx
        mov     ax,250dh                ;get real mode call back address
        int     21h
        mov     edi,eax                 ;real mode call back address
        pop     ebx                     ;real mode procedure cs:ip
        mov     edx,ss:[esp+24]         ;mask to pass to mouse driver
        xor     ecx,ecx                 ;pass zero parameters on stack
        mov     ax,250eh                ;call real mode procedure in ebx
        int     21h
        pop     edi
        pop     esi
        pop     ebx
        pop     ebp
        mov     eax,[esp+4]             ;pointer to c function
        mov     cfuncaddr,eax
        mov     word ptr stack_ptr[4],ds
;eax is now nonzero, return that value to indicate success.
init_ret:
        push    ds                      ;Set ES to DS.
        pop     es
        ret
mous_err:
        pop     edi
        pop     esi
        pop     ebx
        pop     ebp
        xor     eax,eax                 ;indicate failure
        ret
__x386_mouse_init       endp

comment&
        Shut the mouse driver off.  Returns zero if success.
&
public __x386_mouse_term,__x32_mouse_term
__x32_mouse_term        label   near
__x386_mouse_term       proc    near
        xor     eax,eax
        int     33h
        ret
__x386_mouse_term       endp

comment&
        The function below is called by the real mode procedure mous_call and 
        is passed the registers as the mouse driver passed them.  This 
        procedure switches to a stack with ss = ds, adjusts __x386_stacklow 
        accordingly, pushes the passed parameters on the stack and calls the C 
        function stored in cfuncaddr. 
&
mous_call32     proc    far
;save old __x386_stacklow and set a new value pointing to the bottom of the
;assigned 32 bit stack.
extrn __x386_stacklow:dword
        push    __x386_stacklow
        mov     __x386_stacklow,offset DGROUP:cfuncstack
;This code needs to preserve the high word of all registers, it is part of a
;hardware interrupt handler.  The mouse driver will only preserve the low
;word of each register.
        pushad                  ;preserve all registers
        mov     edi,ss
        mov     esi,esp                 ;save old stack
        lss     esp,fword ptr stack_ptr ;switch stacks
        cld                             ;c functions require cleared DF
;strange sequence of events below supplies correct parameters both on the
;stack and in the registers for the Watcom register based parameter passing.
        push    edx                     ;y coordinate
        movzx   edx,bx                  ;state
        movzx   ebx,cx                  ;x coordinate
        pop     ecx
        movzx   ecx,cx                  ;y coordinate
        push    ecx                     ;y coordinate
        push    ebx                     ;x coordinate
        push    edx                     ;state
        movzx   eax,ax
        push    eax                     ;mask
        call    cfuncaddr
        lea     esp,[esp+16]            ;pop parameters
        mov     ss,edi
        mov     esp,esi                 ;restore old stack
        popad
        pop     __x386_stacklow
        ret                             ;far return to real mode mous_call
dummy:
mous_call32     endp

end32code

start16data
extrn __x386_vm_disable:byte
end16data

start16code

call_back_addr  dd      ?               ;address of DOS32 call back device

comment&
        This procedure should be called with the mask to be passed to the 
        mouse driver in dx. The address of the DOS32 real mode call back 
        device is passed in edi. 

        This real mode procedure calls the mouse driver via int 33h and sets 
        up the mouse signal address to procedure "mous_call".  Whenever 
        the mouse driver calls mous_call, it then in turn calls the 32 bit 
        function mous_call32.
&

mouse_init      proc    far
assume ds:__X386_CODESEG_16
        mov     call_back_addr,edi              ;real mode call back device
        mov     cx,dx                           ;bit mask to pass to driver
        push    cs
        pop     es
        mov     dx,offset mous_call             ;es:dx points to mous_call
        mov     ax,12                           ;mouse driver function 12
        int     33h                             ;set up call back address
        retf                                    ;return to 32 bit code
mouse_init      endp

comment&
        The procedure below is called by the mouse driver as indicated by the 
        bit mask passed by the function above.  This procedure then calls the 
        32 bit function whose offset is stored in addr32func.  Remember, ds is 
        undefined at this point.
&
mous_call       proc    far
        pushf
        push    __X386_GROUP_16
        pop     ds              ;load ds with 16 bit data selector
assume ds:__X386_GROUP_16
        inc     ds:__x386_vm_disable
;instruction above disables VM (except under DPMI hosts) since this is a
;hardware interrupt handler.  If a fault occurs it will cause a register
;dump rather than attempting to access the disk.
        db      66h             ;push dword below
        push    0               ;push a dword zero for pointer to segments
        push    0               ;dummy space for protected mode cs
;masm can't be convinced to push a 32 bit offset so do it the hard way......
        db      66h                     ;size prefix
        db      68h                     ;push immediate
        dd      offset mous_call32      ;offset of protected mode procedure
        cli     ;must prevent nested hardware interrupts under Windows
        call    cs:call_back_addr       ;call 32 bit function mous_call32
        add     sp,10                   ;pop parameters off stack
        popf
        dec     ds:__x386_vm_disable    ;restore original vm_disable state
        ret                             ;return to mouse driver
assume ds:nothing
mous_call       endp
end16code

endif   ;MOUSE

ifdef MMFIO

start32code
comment&
void *_x32_mmfio_open(int fd, int size)  Must pass an open file 
        handle, and a nonzero size.
&

extrn __x386_malloc:dword,__x386_free:dword
public __x32_mmfio_open,__x32_mmfio_flush
__x32_mmfio_open:
        push    ebx
        movzx   ebx,word ptr ss:[esp+8] ;file handle
        mov     ecx,ss:[esp+12]
        mov     ax,350eh                ;map file to memory
        int     21h
        jc short mmfio_err1
        mov     eax,ecx                 ;near pointer to mmfio block
        pop     ebx
        ret

mmfio_err1:;X-32 failed the call, attempt to write the file directly into memory
        push    ecx                     ;size of block to map
        xor     ecx,ecx
        xor     edx,edx
        mov     ax,4200h                ;set pointer relative to start of file
        int     21h
        jc short mmfio_err2
;We will malloc a block of memory and write the file into it.  Malloc 8 extra 
;bytes to store the file handle and size.
        mov     eax,ss:[esp]            ;size
        add     eax,8                   ;increase size for data storage.
        push    eax                     ;pass parameters on stack and in eax
        call    __x386_malloc
        pop     ecx                     ;garbage
        or      eax,eax                 ;check if not enough memory
        jz short mmfio_err2
        pop     ecx
        mov     ds:[eax],ecx            ;size of mmfio block
        mov     ds:[eax+4],ebx          ;file handle
        lea     edx,[eax+8]             ;location for read from file
        push    edx                     ;return value for eax if successful
        mov     ah,3fh
        int     21h                     ;read file
        jc short mmfio_err3
        pop     eax                     ;return pointer to file
        pop     ebx
        ret

mmfio_err3:     ;error after malloc, free memory and return error
        pop     eax
        sub     eax,8                   ;point to start of block
        push    eax                     ;pass pointer in eax and on stack
        call    __x386_free
mmfio_err2:     ;return zero to indicate error
        pop     ecx                     ;pop garbage
        pop     ebx
        xor     eax,eax                 ;indicate error
        ret

comment &
        int _x32_mmfio_flush(void *)
        Pass a pointer to a previously allocated mmfio block.  Flushes all 
        changes in the memory block to the file.  Returns 1 if success, 0 if 
        failure.
&
__x32_mmfio_flush: 
        mov     ecx,ss:[esp+4]          ;pointer to mmfio block
        mov     ax,350fh
        int     21h
        jc short mmfio_flush_err1
        mov     eax,1                   ;indicate success
        ret

mmfio_flush_err1:
;X-32 failed the call, check if file is loaded directly in memory
        push    ebx
        push    ecx
        test    word ptr ds:[ecx-2],-1  ;check if high word of handle is zero
        jnz short mmfio_flush_err2      ;jmp if invalid pointer
        mov     ebx,ds:[ecx-4]          ;file handle
        xor     ecx,ecx
        xor     edx,edx
        mov     ax,4200h                ;set file pointer to zero
        int     21h
        jc short mmfio_flush_err2       ;jmp if invalid handle
        pop     ecx                     ;size of mmfio block
        mov     ah,40h
        mov     edx,ecx                 ;pointer to block
        mov     ecx,ds:[ecx-8]          ;size of block
        int     21h                     ;write to file
        jc short mmfio_flush_err3
        pop     ebx
        mov     eax,1                   ;indicate success
        ret

mmfio_flush_err2:
        pop     ecx                     ;pop garbage
mmfio_flush_err3:
        pop     ebx
        xor     eax,eax                 ;indicate error
        ret

end32code
endif ;MMFIO

ifdef STACK
start32data
public __x32_stack_size
__x32_stack_size                 dd      16*1024
end32data
endif ;STACK
end
