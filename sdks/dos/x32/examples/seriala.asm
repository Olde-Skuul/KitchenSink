; Copyright Prototronics
; Totem Lake P.O. 8117
; Kirkland, Washington 98034

; Joe Huffman 
; September 19, 1989
; (206) 820-1972

        include macros.asm

c_public serial_port_init, serial_port_term

        begdata

serial_port_buffer struc        ;DON'T change this structure without looking
                                ;at the corresponding c++ code.  Structures
send_buffer     dd      ?       ;must match.
send_head_p     dd      ?
send_tail_p     dd      ?
receive_buffer  dd      ?
receive_head_p  dd      ?
receive_tail_p  dd      ?
send_bytes      dw      ?
receive_bytes   dw      ?
buf_size        dw      ?
old_int_vec     dd      ?
com_port_addr   dw      ?
int_number      db      ?
eoi_indicator   db      ?
serial_port_buffer ends

com1_buffer_struc_p     dd      ?
com2_buffer_struc_p     dd      ?

        enddata

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

        begcode serialasm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Service the interrupt.
;September 19, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
com2_server:
        push    si
        push    ds

        mov     si,dgroup
        mov     ds,si
        lds     si,com2_buffer_struc_p

        jmps    com_common_server


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Service the interrupt.
;September 19, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
com1_server:
        push    si
        push    ds

        mov     si,dgroup
        mov     ds,si
        lds     si,com1_buffer_struc_p

com_common_server:
        sti

        push    ax
        push    dx
        push    di
        push    es

which_interrupt:
        mov     dx,com_port_addr [si]
        mov     di,INTR_IDENT_OFFSET
        add     dx,di                   ;Figure out which interrupt this is.
        in      al,dx                   ;AL has the interrupt id code.
        sub     dx,di                   ;Leave dx with port address.

        test    al,INTR_REC_DATA        ;Is there data waiting?
        jnz     data_waiting

        test    al,INTR_TRAN_EMPTY      ;Read to send data?
        jnz     send_byte

unknown_interrupt:
        jmp     short all_done


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;The send server.
send_byte:
        mov     ax,send_bytes[si]
        or      ax,ax                   ;Any bytes to send?
        jnz     do_send

        add     dx,INTR_ENABLE_OFFSET   ;No bytes to send so turn off
        in      al,dx                   ;transmit interrupts.
        and     al,NOT TRAN_DATA_INTR
        out     dx,al

        jmp     short server_done

do_send:
        les     di,send_tail_p [si]
        mov     al,es:[di]

if TRAN_REG_OFFSET                      ;If offset is non-zero
        add     dx,TRAN_REG_OFFSET
endif
        out     dx,al

        dec     send_bytes [si]

        inc     di                      ;Pointer to send_buffer.
        mov     ax,di
        sub     ax,word ptr send_buffer [si]
        cmp     ax,buf_size [si]
        jb      send_done               ;No wrap around.

        mov     di,word ptr send_buffer [si]

send_done:
        mov     word ptr send_tail_p[si],di
        jmp     short server_done


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;The receive server.
data_waiting:
if REC_REG_OFFSET
        add     dx,REC_REG_OFFSET
endif
        in      al,dx           ;AL has the input data.

        mov     di,receive_bytes [si]
        cmp     di,buf_size [si]

        jae     server_done     ;Overflow.

        inc     di              ;Bytes received.
        mov     receive_bytes [si],di

        les     di,receive_head_p [si]
        cld
        stosb

        mov     ax,di           ;Receiver head_p
        mov     dx,word ptr receive_buffer [si]
        sub     ax,dx
        cmp     ax,buf_size [si]        ;Wrap around?

        jb      receive_done
        mov     di,dx                   ;receiver_buffer to di.

receive_done:
        mov     word ptr receive_head_p [si],di

server_done:
        jmp     short which_interrupt   ;Check to see if another interrupt had
                                        ;occurred.

all_done:
        mov     al,eoi_indicator [si]   ;Enable this interrupt to occur again.
        out     I8259_END_OF_INTR_PORT,al

        pop     es
        pop     di
        pop     dx
        pop     ax
        pop     ds
        pop     si
        iret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Install the interrupt handler.  Return NO_INTERRUPT if unable 
;to install the interrupt.
;September 20, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
func    serial_port_init

        incBP
        push    bp
        mov     bp,sp
        push    si

if LPTR
        les     si,P[bp]
else
        mov     si,P[bp]
ife ESeqDS
        mov     ax,ds
        mov     es,ax
endif
endif

        mov     ah,35h                  ;Get an interrupt.

        push    es
        mov     al,es:int_number [si]   ;The interrupt to get from DOS.
        int     21h

        mov     ax,es
        pop     es

        mov     word ptr es:(old_int_vec + 2)[si],ax
        mov     word ptr es:old_int_vec[si],bx

        mov     bx,cs                   ;Segment of int service routine.

        mov     dx,offset com1_server
        mov     al,es:int_number [si]   ;The interrupt to install.
        cmp     al,COM1_INT
        jz      install_1

        cmp     al,COM2_INT
        jz      install_2

        mov     ax,NO_INTERRUPT         ;Not com1 and not com2.  Ignore it.
        jmps    done                    ;return unable to install interrupt.

install_2:
        mov     dx,offset com2_server
        mov     word ptr com2_buffer_struc_p,si
        mov     word ptr com2_buffer_struc_p + 2,es
        jmps    install

install_1:
        mov     word ptr com1_buffer_struc_p,si
        mov     word ptr com1_buffer_struc_p + 2,es

install:
        push    ds
        mov     ds,bx                   ;ds:dx points to server.
        mov     ah,25h                  ;al has int number.
        int     21h
        pop     ds

        clr     ax                      ;Return 0.

done:
if ESeqDS
        mov     bx,ds
        mov     es,bx
endif
        pop     si
        pop     bp
        decBP
        ret

c_endp  serial_port_init

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Uninstall the interrupt.
;September 19, 1989
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
func    serial_port_term
        incBP
        push    bp
        mov     bp,sp
        push    si
        push    ds

if LPTR
        lds     si,P[bp]
else
        mov     si,P[bp]
endif

        mov     ah,25h                  ;Install an interrupt.
        mov     al,int_number [si]

        lds     dx,old_int_vec [si]     ;The old interrupt.

        int     21h                     ;Do the (un)install.

        pop     ds
        pop     si
        pop     bp
        decBP
        ret

c_endp  serial_port_term

        endcode serialasm
        end

