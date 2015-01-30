; Copyright Prototronics 1992
; 6490 Kaniksu Shores Circle
; Sandpoint, ID  83864-9445
; Joe Huffman
;
; Original version, September 19, 1989
; Modified for X-32VM on August 14, 1992
; email: joe@proto.com
; FAX:   208-263-8772

        include mac32.asm

        start32data

serial_data_start       label   byte

serial_port_buffer struc        ;DON'T change this structure without looking
                                ;at the corresponding c++ code.  Structures
send_buffer     dd      ?       ;must match.
send_head_p     dd      ?
send_tail_p     dd      ?
receive_buffer  dd      ?
receive_head_p  dd      ?
receive_tail_p  dd      ?
send_bytes      dd      ?
receive_bytes   dd      ?
buf_size        dd      ?
old_int_vec     df      ?
                dw      ?       ;Padding.
com_port_addr   dd      ?
int_number      db      ?
eoi_indicator   db      ?
serial_port_buffer ends

com1_buffer_struc_p     dd      ?
com2_buffer_struc_p     dd      ?

ds_dgroup       dw      ?

serial_data_size        equ     $ - serial_data_start
        end32data

NO_INTERRUPT            equ     2       ;Also define in c++ code. Must be same.

I8259_END_OF_INTR_PORT  equ     20h

;Interrupt enable bits.
REC_DATA_INTR           equ     1
TRAN_DATA_INTR          equ     2
REC_STATUS_INTR         equ     4

;Interrupt ID defines.
INTR_REC_DATA           equ     4       ;Received data availiable.
INTR_TRAN_EMPTY         equ     2       ;Transmit holding register is empty.

REC_REG_OFFSET          equ     0
TRAN_REG_OFFSET         equ     0
INTR_ENABLE_OFFSET      equ     1
INTR_IDENT_OFFSET       equ     2

COM1_INT        equ     0ch
COM2_INT        equ     0bh

P               equ     8       ;Offset to first parameter on the stack.

        start32code

serial_code_start:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Service the interrupt.
;September 19, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
com2_server:
        push    ds
        push    esi
        mov     si,cs:ds_dgroup
        mov     ds,si

        mov     esi,com2_buffer_struc_p
        jmp     short com_common_server


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Service the interrupt.
;September 19, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
com1_server:
        push    ds
        push    esi
        mov     si,cs:ds_dgroup
        mov     ds,si

        mov     esi,com1_buffer_struc_p

com_common_server:
        sti

        push    eax
        push    edx
        push    edi

which_interrupt:
        mov     edx,[esi].com_port_addr
        mov     di,INTR_IDENT_OFFSET
        add     edx,edi                 ;Figure out which interrupt this is.
        in      al,dx                   ;AL has the interrupt id code.
        sub     dx,di                   ;Leave dx with port address.

        test    al,INTR_REC_DATA        ;Is there data waiting?
        jnz     short data_waiting

        test    al,INTR_TRAN_EMPTY      ;Read to send data?
        jnz     short send_byte

unknown_interrupt:
        jmp     short all_done


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;The send server.
send_byte:
        mov     eax,[esi].send_bytes
        or      eax,eax                 ;Any bytes to send?
        jnz     short do_send

        add     dx,INTR_ENABLE_OFFSET   ;No bytes to send so turn off
        in      al,dx                   ;transmit interrupts.
        and     al,NOT TRAN_DATA_INTR
        out     dx,al

        jmp     short server_done

do_send:
        mov     edi,[esi].send_tail_p
        mov     al,[edi]
        inc     edi

if TRAN_REG_OFFSET                      ;If offset is non-zero
        add     dx,TRAN_REG_OFFSET
endif
        out     dx,al

        dec     [esi].send_bytes

        mov     eax,edi                 ;Pointer to send_buffer.
        sub     eax,[esi].send_buffer
        cmp     eax,[esi].buf_size
        jb      short send_done         ;No wrap around.

        mov     edi,[esi].send_buffer

send_done:
        mov     [esi].send_tail_p,edi
        jmp     short server_done


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;The receive server.
data_waiting:
if REC_REG_OFFSET
        add     dx,REC_REG_OFFSET
endif
        in      al,dx           ;AL has the input data.

        mov     edi,[esi].receive_bytes
        cmp     edi,[esi].buf_size

        jae     short server_done       ;Overflow.

        inc     edi                     ;Bytes received.
        mov     [esi].receive_bytes,edi

        mov     edi,[esi].receive_head_p
        mov     [edi],al
        inc     edi                     ;Increment the pointer.

        mov     eax,edi                 ;Receiver head_p
        mov     edx,[esi].receive_buffer
        sub     eax,edx
        cmp     eax,[esi].buf_size      ;Wrap around?

        jb      short receive_done
        mov     edi,edx                 ;receiver_buffer to EDI.

receive_done:
        mov     [esi].receive_head_p,edi

server_done:
        jmp     short which_interrupt   ;Check to see if another interrupt had
                                        ;occurred.

all_done:
        mov     al,[esi].eoi_indicator  ;Enable this interrupt to occur again.
        out     I8259_END_OF_INTR_PORT,al

        pop     edi
        pop     edx
        pop     eax
        pop     esi
        pop     ds
        iretd

;Don't move this equate without careful analysis.
serial_code_size        equ     $ - serial_code_start

extrn   __x386_memlock:near, __x386_memunlock:near

;;;;;;;;;;;;;;;;;;;;;;;;;
; Lock the memory accessed as interrupt time.
; int lock_mem_helper(struct serial_port_buffer *p, 
;                     int (*func)(void _far *p, unsigned int length)
; Returns 0 if successful, -1 if failure.
; August 14, 1992
;;;;;;;;;;;;;;;;;;;;;;;;;
lock_mem_helper proc    near
        push    ebp
        mov     ebp,esp
        push    ebx
        push    esi

        mov     esi,P + 4[ebp]          ;Function to call.

        push    serial_data_size
        push    ds
        push    offset DGROUP:serial_data_start
        call    esi                     ;Either lock or unlock the memory.
        add     esp,12
        or      eax,eax
        jnz     short lock_done

        push    serial_code_size
        push    cs
        push    offset serial_code_start
        call    esi
        add     esp,12
        or      eax,eax
        jnz     short lock_done

        mov     ebx,P[ebp]              ;The buffer structure pointer.
        push    [ebx].buf_size
        push    ds
        push    [ebx].send_buffer
        call    esi
        add     esp,12
        or      eax,eax
        jnz     short lock_done

        push    [ebx].buf_size
        push    ds
        push    [ebx].receive_buffer
        call    esi
        add     esp,12
        or      eax,eax
        jnz     short lock_done

        push    50              ;size of serial port buffer
        push    ds
        push    ebx
        call    esi
        add     esp,12

lock_done:
        pop     esi
        pop     ebx
        pop     ebp
        ret
lock_mem_helper endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Install the interrupt handler.  Return NO_INTERRUPT if unable 
;to install the interrupt.
;September 20, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
public _serial_port_init
_serial_port_init       proc    near
        push    ebp
        mov     ebp,esp
        push    esi
        push    ebx

        mov     ds_dgroup,ds            ;Save DGROUP for later use

        mov     eax,offset __x386_memlock
        push    eax
        mov     esi,P[ebp]              ;Get the pointer to the struct
        push    esi
        call    lock_mem_helper         ;Need to lock the memory.
        add     esp,8

        or      eax,eax
        jnz     short init_fail

        mov     ax,2502h                ;Get an interrupt (X-32VM call).
        mov     cl,[esi].int_number     ;The interrupt to get from DOS.
        int     21h

        mov     word ptr  [esi].old_int_vec + 4,es
        mov     dword ptr [esi].old_int_vec,ebx

        mov     cl,[esi].int_number     ;The interrupt to install.
        mov     edx,offset com1_server

        cmp     cl,COM1_INT
        jz      install_1

        cmp     cl,COM2_INT
        jz      install_2

init_fail:
        mov     eax,NO_INTERRUPT        ;Not com1 and not com2.  Ignore it.
        jmp     short done              ;Return unable to install interrupt.

install_2:
        mov     edx,offset com2_server
        mov     com2_buffer_struc_p,esi
        jmp     short install

install_1:
        mov     com1_buffer_struc_p,esi

install:
        mov     bx,cs                   ;Segment of int service routine.

        push    ds
        mov     ds,bx                   ;DS:EDX points to server.
        mov     ax,2506h                ;CL has int number.
        int     21h
        pop     ds

        xor     eax,eax                 ;Return 0.

done:
        push    ds
        pop     es
        pop     ebx
        pop     esi
        pop     ebp
        ret

_serial_port_init       endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Uninstall the interrupt.
;September 19, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

public  _serial_port_term
_serial_port_term       proc    near
        push    ebp
        mov     ebp,esp
        push    ds

        mov     eax,P[ebp]
        mov     cl,[eax].int_number
        lds     edx,[eax].old_int_vec   ;The old interrupt.
        mov     ax,2504h                ;Install an interrupt.
        int     21h                     ;Do the (un)install.

        mov     eax,offset __x386_memunlock
        push    eax
        push    P[ebp]
        call    lock_mem_helper         ;Release the memory previously locked.
        add     esp,8

        pop     ds
        pop     ebp
        ret

_serial_port_term       endp

        end32code
        end

