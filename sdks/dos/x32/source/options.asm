comment &
        This file contains variables which can be adjusted by the user for the 
        purpose of modifying the behavior of the X-32 DOS extender.  The 
        variables below can be adjusted within the described guidelines and 
        then assembled and linked with an X-32 application to customize 
        certain aspects of the extender.  Conditional assembly is used to 
        produce two seperate modules, the conditional statements can be 
        removed and the file assembled in one module if desired.  These 
        variables can be adjusted at run time only if the description 
        specifically allows it, most of them must not be altered after link 
        time. 
&
ifdef OPT1
__X386_DATASEG_16      segment dword public 'DATA16'

comment &
        The variable below affects the size of the buffer which X-32 uses for 
        communicating to DOS.  Increasing the size of this buffer will 
        sometimes speed up disk IO but it will reduce the amount of memory 
        available which can be allocated by the application.  It will also 
        reduce the amount of conventional memory which can be reserved for DOS 
        or allocated with int 21h function 48h.

        This size must always be an even number of 4 kbyte pages.  The default 
        size is 4 pages or 16 kbytes.  It must never be set to a value smaller 
        than 1 page or 4 kbytes and must never be larger than 15 pages or 60 
        kbytes.
&

public __x386_dos_buffer_size
__x386_dos_buffer_size  dd      4 * 4096

comment &
        The variable below is determines how much conventional memory is 
        reserved for DOS under non DPMI operating systems.  If X-32 is using a 
        DPMI host, this variable has no effect and the maximum amount of 
        memory possible with the specified DOS buffer size is reserved for DOS 
        but can also be allocated for the application through int 21h function 
        48h. 

        If there is no DPMI host, X-32 will attempt to reserve the number of 4 
        kbyte pages specified in the byte quantity below.  This reserved 
        memory will NOT be available to the application through int 21h 
        function 350ch.  It can be used by DOS for its own purposes or 
        allocated with int 21h function 48h.  It is sometimes necessary to 
        reserve memory for DOS to support certain function calls such as int 
        21h function 67h, spawn or exec. 

        The default value is 0 which means that all conventional memory is 
        allocated by X-32 and will be available to the application through int 
        21h function 350Ch or int 21h function 48h.  If the value below is set 
        to 255, this will attempt to reserve 255 * 4 kbytes or nearly 1 
        megabyte of conventional memory.  In this case X-32 will reserve the 
        maximum amount of memory possible with the specified DOS buffer size.  
        That memory will not be available to the application through function 
        call 350ch.  Acceptable values for this variable are 0 - 255. 
&
public __x386_conv_mem_resv
__x386_conv_mem_resv    db      0
__X386_DATASEG_16       ends

endif ;OPT1

ifdef OPT2
__X386_DATASEG_16      segment dword public 'DATA16'
comment &
        The variables below control certain characteristics of the virtual 
        memory manager when using X-32VM.  These variables will have no effect 
        on the non virtual memory extender and will also have no effect when 
        using X-32VM under a DPMI host such as windows or OS2.  Also note that 
        when assembling this file, the variables below will show up only if
        -dVM is on the command line to the assembler.
&

comment &
        The variables below are used to reserve a specific address for the 
        memory mapped file IO space under non DPMI situations.  

        Some systems which have very large free disk space will have enough of 
        the 3.5 Gbytes of available linear address space used up with code, 
        data, allocatable heap space and allocatable stack space that there is 
        no guaranteed free linear address space for memory mapped file IO.  
        For example, the stack could possibly grow down by the amount of swap 
        space available or the heap can grow up by the amount of swap space 
        available.  Thus 2 GBytes of free swap space would make it impossible 
        to guarantee that any given linear address will not be overwritten by 
        stack or heap.  The variables below limit how far up the heap can grow 
        and how far down the stack can grow.  The space between these two 
        DGROUP relative pointers is the space reserved for memory mapped file 
        IO. 

        The variable __x386_mmfio_bottom defines the starting location of 
        memory mapped file IO and the upper limit of the heap.  The default 
        value is 2 Gbytes which means that code, data and heap space is 
        limited to 2 Gbytes and the first memory mapped file will be located 
        at 2 Gbytes (relative to DGROUP).  If an application does not use 
        memory mapped file IO and may possibly be used in a situation where 
        greater than 2 Gbytes of code, data and heap would be required, this 
        variable should be set to 0fffff000h which means the heap will be 
        limited only by heap growing into the stack or by available swap 
        space.  This variable must always be 4 kilobyte aligned which means 
        the 12 LSBs must be zero.  This variable must never be set to a value 
        smaller than the size of the code and static data. 

        The variable __x386_mmfio_top defines the upper most location of 
        memory mapped file IO and the lower most location which the stack will 
        be allowed to grow down to.  The default value is C0000000h which 
        when used with the default value for __x386_mmfio_bottom allows 1 
        Gbyte for memory mapped file IO.  Since the stack starts at about 
        E0000000h, this reserves 500 megabytes for stack space.  If the 
        application does not use memory mapped file IO and may require a stack 
        larger than 500 megabytes, this variable can be set to 0 which will 
        reserve nothing for memory mapped file IO and the stack will be 
        allowed to grow downwards until it reaches the heap (or until the 
        system runs out of free swap space).  This variable should never be 
        set to a value approaching E0000000h as that will prevent the stack 
        from growing downwards properly.
&
public __x386_mmfio_bottom,__x386_mmfio_top
__x386_mmfio_bottom     dd      80000000h      ;2 Gbyte upper limit for the heap

__x386_mmfio_top        dd      0C0000000h     ;lower limit for the stack

comment &
        The variable below affects the enabling and disabling of VM in 
        situations where the free disk space is less than the available 
        physical memory.

        If the following variable is set to 1 (the default), X-32VM will 
        disable VM if the free disk space + code size is less than the 
        available physical memory.  This insures that the application will 
        have the maximum amount of memory available in all situations.  If 
        memory mapped file IO is used by the application, VM must not be 
        disabled.  If VM is disabled, all calls to the memory mapped file IO 
        functions will fail.

        If the following variable is set to 2, VM will always be enabled 
        except on systems where X-32VM is forced to use a DPMI host such as 
        Windows or OS2.  Thus this variable should be set to 2 if memory 
        mapped file IO is used. 

        Setting it to 0 disables VM.
&

public __x386_vm
__x386_vm               db      1       ;maximize available memory

comment &
        The variable __x386_reserve_swapfile_space controls the behavior of 
        the virtual memory manager in managing the swap file. 

        The bits of this variable are defined as follows:

        Bit 0   EN (reserve ENable)
        Bit 1   FL (FilL)
        Bit 2   DL (DeLay)
        Bit 3   MAM (Maximize Available Memory)
        Bits 4 - 7 are reserved and should be set to zero

        The EN bit enables or disables the disk space reservation option.  The 
        default value is 0 which disables reservation of disk space.  If this 
        feature is disabled, the extender will only use disk space as it is 
        actually needed for swapping and will result in the fastest possible 
        execution time.  With this feature disabled, X-32VM will only allocate 
        disk space when it is actually needed for swapping.  X-32VM may allow 
        an application to allocate a large block of memory while there is 
        plenty of disk space available but since that disk space is not 
        immediately reserved, additional files written to disk after 
        allocating the memory block may reduce the disk space to the point 
        where there is insufficient disk space to support the allocated 
        virtual memory.  This can cause unexpected termination of the 
        application due to failure during VM disk IO. 

        If EN = 1, the extender will expand the swapfile to support the 
        Virtual memory space requested at the time the memory is allocated 
        rather than when the space is required for swapping.  This may result 
        in slower execution times when allocating memory but once allocated, 
        the memory is accessible at the same speed as it would be with a zero 
        value.  Nonzero values are recommended for applications which write 
        large files to disk, which use a network for swapfile purposes or any 
        application which operates in a situation where the available disk 
        space may fluctuate and cause the extender to run out of swap space 
        unexpectedly. 

        When EN = 0, the setting of FL and DL will be ignored.  When set to 1, 
        the disk space reservation option is enabled and its precise behavior 
        will be determined by FL and DL as described below. 

        The FL bit controls how the extender expands the swap file.  When set 
        to zero, the swap file is expanded to reserve disk space by 
        positioning the file pointer at the desired end of file and writing 0 
        bytes to the file.  The specifications for Microsoft DOS dictate that 
        the file will be expanded to the desired size following this sequence 
        of events.  While all versions of DOS tested seem to behave correctly 
        in regards to this, there seems to be some types of network software 
        which do not properly reserve disk space in this situation.  If the X-
        32VM extender is asked to reserve space for a swapfile on a network 
        with this problem, the FL bit should be set to 1.  With FL = 1, the 
        extender expands the swap file by positioning the file pointer at the 
        end of file and then filling the file with garbage to expand it to the 
        desired size.  This garbage is overwritten with data from memory as VM 
        swapping occurs so the garbage will never show up in the applications 
        memory.  This method of reserving disk space for the swap file should 
        work with all versions of network software but it can be much slower 
        when first allocating memory than with FL = 0. 

        The DL bit controls when the extender starts reserving space.  When 
        set to 0, the extender will reserve disk space even if it has 
        sufficient physical memory to support the present memory requirements, 
        thus it may be writing to disk unneccesarily during a malloc().  When 
        set to 1, the extender will "delay" reserving disk space until it is 
        obvious that VM will be needed to support the memory requirements of 
        the application.  This will have the effect of greatly speeding up 
        allocation of memory in situations where there is sufficient memory to 
        support the application without using VM.  There is a problem with 
        setting this bit to 1 in applications which use the memory mapped file 
        IO and the physical address mapping features of X-32.  If one or more 
        of these features are in use, the extender may not correctly detect 
        when it has exceeded the memory it can support without VM.  If these 
        features are in use and the extender is required to reserve disk 
        space, the delay feature should be disabled (DL = 0). 

        The MAM bit can be used to increase the amount of memory available to 
        the application.  The default value of MAM is 0 which is optimum for 
        Virtual memory speed but may result in less available memory than 
        might be expected.  For example if MAM = 0, the machine has 4 megs of 
        physical memory and 6 megs of free disk space, the available memory 
        will be only 6 megs.  The Virtual Memory manager will insist on having 
        enough swap space for each page of data to exist both in physical 
        memory and in the swap file.  This speeds up the performance of the 
        system by eliminating the need to write unchanged pages back to disk 
        when swapping them out.  If MAM = 1, the total memory available to 
        an application running on the machine described above will = 10 
        megabytes.  Space in the swap file will be freed anytime a page is 
        read from it into physical memory.  This means that anytime a page is 
        swapped out, it must be written back to disk even if it hasn't been 
        changed since the last time it was swapped.  For this reason, setting 
        the MAM bit can in the worst case cause a 2:1 performance degredation 
        in VM speed.

        Non of these bits will have any effect when operating under a DPMI 
        host since the host is in complete control of virtual memory activity. 

        This variable can be initialized to any value by changing this file 
        and reassembling with -dVM or it can be changed at runtime using the 
        selector, __x386_data_16_alias.  Example code to change this variable 
        is below: 

start16data
extrn __x386_reserve_swapfile_space:byte
end16data

start32code

func_name:      ;call this function to turn on swapfile space reservation
        push    es              ;es must be preserved with some compilers
extrn __x386_data_16_alias:word
        mov     es,__x386_data_16_alias
assume es:__X386_GROUP_16
;Set EN = 1, FL = 0, DL = 1
        mov     es:__x386_reserve_swapfile_space,5
        pop     es
assume es:nothing
        ret

end32code
&

public __x386_reserve_swapfile_space
__x386_reserve_swapfile_space   db      0       ;disable disk space reservation

__X386_DATASEG_16       ends

endif ;OPT2

ifdef OPT3
.386
__X386_DATASEG_16      segment dword use16 public 'DATA16'

extrn __x386_vm_swap_name:byte,__x386_vm_swap_handle:word

__X386_DATASEG_16       ends
comment &
        The function, "__x386_open_swap_file" is used for opening a Virtual 
        memory swap file.  This function is always called during initilization 
        for the VM version of the extender.  This IS REAL MODE 16 BIT CODE.  
        The function is passed the psp segment in ax which can be used to get 
        the environment segment which in turn is used to search for 
        environment variables.  This function must open a swap file in 
        read/write mode and place the handle in the variable, 
        __x386_vm_handle.  It must place the name of the file in the buffer, 
        __x386_vm_swap_name.  Placing a zero in the first byte of 
        __x386_vm_swap_name will disable VM, this should be done if for some 
        reason, the function below cannot open an acceptable swap file.  The 
        function can trash all registers except ds which equals ss which 
        equals __X386_DATASEG_16.  The function must return with a near 
        return.

        The default function provided below searches for the environment 
        variable tmp or temp and if found, it opens a swap file in the 
        specified path.  If it cannot find either of those environment 
        variables, it checks drives starting with C: and ending with the first 
        unacceptable drive letter, it then uses the largest drive found.  The 
        programmer may modify, adjust or replace this code as desired to 
        achieve the desired behavior for opening a swap file.
&

__X386_CODESEG_16       segment para use16 public 'CODE'
if @Version GE 600
assume ds:__X386_DATASEG_16,es:nothing,fs:nothing,gs:nothing,ss:nothing
else
assume cs:__X386_CODESEG_16,ds:__X386_DATASEG_16,es:nothing,fs:nothing,gs:nothing,ss:nothing
endif

public __x386_open_swap_file
__x386_open_swap_file   proc    near
        sub     sp,1024         ;allocate a 1 kilobyte buffer on the stack
;First check for TMP or TEMP environment variables.
        mov     di,offset __X386_DATASEG_16:__x386_vm_swap_name
        push    ds
        pop     es                      ;es:di points to swapname buffer
        mov     ds,ax                   ;psp
        mov     ds,ds:[2ch]             ;get environment segment in ds
        cld
        xor     si,si
        jmp     search_1                ;don't check for leading zero at first
tmp_search_loop:                        ;find the next zero
        lodsb
        or      al,al
        jnz     tmp_search_loop         ;jmp if not zero
search_1:       ;ds:si points to start of an environment parameter
        mov     eax,ds:[si]             ;get 4 bytes from environment
        cmp     eax,'PMET'              ;check for TEMP
        je      temp_found
        cmp     eax,'=PMT'              ;check for TMP=
        je      tmp_found
        or      al,al                   ;check for two consecutive zeroes
        jz short tmp_search_fail        ;jmp if at end of environment
        inc     si
        jnz     tmp_search_loop
tmp_search_fail:    ;no environment variables found, check space on disk drives
        xor     edi,edi                 ;largest disk space thus far
        mov     esi,'\:b'               ;will be incremented to drive C
        mov     ebp,esi
        inc     ebp                     ;largest drive thus far
        push    ss
        pop     ds                      ;restore ds
tmp_loop2:
        inc     si
        mov     dword ptr __x386_vm_swap_name,esi
;we will check the "device type" to see if the drive is a hard drive or not
        mov     dx,sp   ;we use space on the stack for a buffer, ss = ds
        mov     ax,440dh        ;get block device parameters
        mov     cx,860h         ;get disk drive information
        lea     bx,[si-96]      ;convert to drive number, 1 = a: etc
        int     21h
        jc short tmp_loop_exit  ;jmp if invalid drive
        mov     dl,bl           ;drive letter, 1 = a: etc.
        mov     bx,sp
        cmp     byte ptr ds:[bx+1],5    ;check if it is a hard drive
        jne short tmp_loop_exit
;It is a hard drive, now check the available space on the specified drive. 
        xor     eax,eax                         ;return zero if no file open
        xor     ebx,ebx
        xor     ecx,ecx
        mov     ah,36h                          ;get drive information
        int     21h
        jc short tmp_loop_exit  ;jmp if invalid drive.
;ecx = bytes/sector, eax = sectors/cluster, ebx = available clusters
        mul     ecx                     ;eax*ecx
        mul     ebx                     ;total bytes on disk now in eax:edx
        or      edx,edx                 ;check if carry into edx
        jz short no_carry               ;jmp if less than 4 G bytes
        mov     eax,-1                  ;drive space is very large
no_carry:
        cmp     eax,edi
        jbe short smaller_drive         ;jump if new drive is smaller than edi
        mov     edi,eax                 ;new largest drive
        mov     ebp,dword ptr __x386_vm_swap_name       ;new largest drive
smaller_drive:
        cmp     si,':z'                         ;check if > z
        jb      tmp_loop2

tmp_loop_exit:          ;largest drive is in ebp
        mov     dword ptr __x386_vm_swap_name,ebp
        mov     ah,5ah                  ;create temporary file
        xor     cx,cx
        mov     dx,offset __X386_DATASEG_16:__x386_vm_swap_name
        int     21h
        mov     __x386_vm_swap_handle,ax        ;save file handle
        jnc short tmp_file_exit
;error creating file
        mov     word ptr __x386_vm_swap_name,cx ;zero indicates no swap file
        jmp short tmp_file_exit
temp_found:
        inc     si
        mov     al,ds:[si+3]
        cmp     al,'='                  ;check for TEMP=
        jne     tmp_search_loop
tmp_found:
;TEMP= or TMP= is found, ds:[si+3] points to '=', es:di points to buffer
        mov     dx,di
        add     si,4                    ;point to path name
        mov     cx,15                   ;allow up to 60 bytes in path name
        rep     movsd                   ;asciiz path name is now in buffer
        push    es
        pop     ds                      ;ds:dx points to path name
        or      byte ptr __x386_vm_swap_name,32 ;make drive a small case letter
;CAUTION cx must = 0 at this point
        mov     ah,5ah                  ;create temporary file
        int     21h
        jc      tmp_search_fail                 ;jmp if DOS error
        mov     __x386_vm_swap_handle,ax        ;save file handle
tmp_file_exit:
        add     sp,1024
        ret

__x386_open_swap_file   endp

__X386_CODESEG_16       ends

endif ;OPT3
end
