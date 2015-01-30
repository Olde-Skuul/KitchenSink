// Copyright Prototronics
// Totem Lake P.O. 8117
// Kirkland, Washington 98034

// Joe Huffman 
// September 16, 1989
// (206) 820-1972


#ifndef INCLUDED_SERIAL_H
#define INCLUDED_SERIAL_H

// Serial port code.

typedef enum serial_port_number_enum 
{
  SERIAL_COM1,
  SERIAL_COM2,
  SERIAL_LAST_PORT
} serial_port_number;

typedef enum serial_baud_enum
{ // Numbers correspond to the divisor for the UART.
  SERIAL_50 = 2304, SERIAL_110 = 1047, SERIAL_300 = 384, 
  SERIAL_1200 = 96, SERIAL_2400 = 48, SERIAL_4800 = 24, SERIAL_9600 = 12
} serial_baud;

#if __I86__ < 3
#pragma ZTC align 2 // Make sure the correct alignment is used.
#else
#pragma ZTC align 4
#endif

struct serial_port_buffer
{
#if __I86__ < 3
  unsigned char _far *send_buffer,   _far *send_head_p,   _far *send_tail_p;
  unsigned char _far *receive_buffer,_far *receive_head_p,_far *receive_tail_p;
#else
  unsigned char *send_buffer, *send_head_p, *send_tail_p;
  unsigned char *receive_buffer, *receive_head_p, *receive_tail_p;
#endif
  volatile unsigned int send_bytes, receive_bytes;
  unsigned int buf_size;
  void (_far * old_int_vec)(void);  // Used in the asm code.
  unsigned int com_port_addr;       // Used in the asm code.
  unsigned char int_number;         // Used in the asm code.
  unsigned char eoi_indicator;      // Used in the asm code.
};
#pragma ZTC align   // Restore the default alignment.

struct serial_port_registers
{
  unsigned int divisor;
  unsigned char line_cntr_reg, intr_enable_reg, modem_reg, enable_8259_mask;
};

class serial
{
// These are the currently active buffer pointers.
  static struct serial_port_buffer serial_buffers[SERIAL_LAST_PORT];

  int status_val;
  serial_port_number port;
  unsigned int modem_port_addr;
  struct serial_port_buffer old_buffer; // Watch it carefully, these are NOT 
                                        // the currently active buffers.
                                        // It is the last active ones.
  struct serial_port_registers old_registers;  // Last active register values.

void port_init (void);
void port_term (void);

public:
serial(serial_port_number port_num,unsigned int size_of_buffer, serial_baud b);
~serial (void);

/****************************************************************************
Return 0 if the everything is okay.  Return ASCII string of error message if
there is a problem.  Like not enough memory for the buffers, whatever.
September 17, 1989
****************************************************************************/
const char *status (void);

/****************************************************************************
Output a byte to the serial port.  Returns the number bytes in the output 
buffer after this byte is put in. 
September 16, 1989
****************************************************************************/
unsigned int put (unsigned char b);

/****************************************************************************
Input a byte from the serial port.  Returns the number of bytes in the input
buffer after this byte is taken out.  Returns ~0 if there were no bytes in the 
buffer.
September 16, 1989
****************************************************************************/
unsigned int get (unsigned char &b);

/****************************************************************************
Get the number of bytes remaining in the receive buffer.
September 16, 1989
****************************************************************************/
unsigned int received_bytes_waiting(void);

/****************************************************************************
Get the number of bytes remaining in the send buffer.
September 16, 1989
****************************************************************************/
unsigned int send_bytes_waiting(void);

/****************************************************************************
Set the baud rate.
September 16, 1989
****************************************************************************/
void baud (serial_baud b);

/****************************************************************************
Clear the receive buffer.  All data in the receive buffer is lost.
September 21, 1989
****************************************************************************/
void receive_clear (void);

/****************************************************************************
Clear the transmit buffer.  All data in the transmit buffer is lost.
September 21, 1989
****************************************************************************/
void transmit_clear (void);

};

#endif
