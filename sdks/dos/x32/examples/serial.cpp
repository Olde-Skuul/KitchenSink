// Copyright FlashTek, Inc. 1992
// 121 Sweet Ave.
// Moscow, Idaho  83843

// Joe Huffman 
// August 17, 1992
// FAX:   208-882-7275
// email: joe@proto.com


#ifdef DEBUG
static char __file__[] = __FILE__;
#define assert(e) ((void)((e) || _assert(__file__,__LINE__)))
extern void _assert(const char *,unsigned);
#else
#define assert(e) ((void)(e))
#endif

#include <stdlib.h>
#include <conio.h>  // Prototypes inp(),inpw(), etc with Watcom.
#include <dos.h>

#include "serial.h"

#ifdef TEST

#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define key_waiting() kbhit()
#define key_input() getch()

#define ESC 27

int main (int argc, char *argv[])
{
  char echo;
  int port_num = 0;

  do
  {
    fputs ("\nEcho received data to sender (Y | N) ?", stdout);
    echo = key_input();
    echo = toupper(echo);
    fputc (echo, stdout);
    fflush(stdout);
  } while (echo != 'Y' && echo != 'N');

  if (echo == 'N')
    echo = 0;

  char buf[150];
  do
  {
    fputs ("\nPort (1 | 2)? ", stdout);
    fflush (stdout);

    port_num = key_input();
    fputc (port_num, stdout);
    fputc ('\n', stdout);
    port_num -= '0';
  } while (port_num != 1 && port_num != 2);

  fflush (stdout);
  serial p (port_num == 1? SERIAL_COM1: SERIAL_COM2, 1000, SERIAL_2400);

  assert (p.status() == 0);

  int i, done = 0;

  for (i = 2000; i > 0; i--)
    p.put ('a');

  do
  {
    unsigned char b;

    while (p.get (b) != ~0)
    {
      if (b == ESC)
        done = 1;

      fputc (b, stdout);

      if (echo)   // Echo back to port?
        p.put (b);

      fflush (stdout);
    }

    if (key_waiting())
    {
      int key = key_input();
      if (key == ESC)
        done = 1;

      p.put (key);
    }
  } while (!done);

  while (p.send_bytes_waiting() != 0)
    ;

  sleep (1);

  return 0;
}

/****************************************************************************
Usual _assert() (for c++ functions).  Report the error and exit.
September 16, 1989
****************************************************************************/
void _assert (const char *file, unsigned line)
{
  printf("\nAssertion failure:\nfile: %s, line: %u\n", file, line);
  exit (1);
}
#endif  // TEST


// Serial port code.

#define NO_MEMORY 1         // Status bits.
#define NO_INTERRUPT 2      // Also defined in asm code.  Must be the same.
#define NO_PORT 4

#define COM1_ADDRESS (0x3f8)        // Port addresses.
#define COM2_ADDRESS (0x2f8)
#define COM1_INT_NUM (0xc)
#define COM2_INT_NUM (0xb)

#define INTR_NUM (modem_port_addr == COM1_ADDRESS? COM1_INT_NUM: COM2_INT_NUM)

#define COM1_EOI_INDICATOR (4 | 0x60)
#define COM2_EOI_INDICATOR (3 | 0x60)

extern "C" int _cdecl serial_port_init (struct serial_port_buffer *p),
               _cdecl serial_port_term (struct serial_port_buffer *p);

static struct serial_port_buffer serial::serial_buffers[SERIAL_LAST_PORT]; // = {{0},{0}};

/****************************************************************************
Initialize the serial port, set up the interrupt service routine.
September 16, 1989
****************************************************************************/
serial::serial (serial_port_number port_num, unsigned int size_of_buffer,
                serial_baud baud_rate)
{
  status_val = 0;
  port = port_num;

  switch (port)
  {
  case SERIAL_COM1:
    old_buffer.com_port_addr = modem_port_addr = COM1_ADDRESS;
    old_buffer.int_number = COM1_INT_NUM;
    old_buffer.eoi_indicator = COM1_EOI_INDICATOR;
    break;

  case SERIAL_COM2:
    old_buffer.com_port_addr = modem_port_addr = COM2_ADDRESS;
    old_buffer.int_number = COM2_INT_NUM;
    old_buffer.eoi_indicator = COM2_EOI_INDICATOR;
    break;

  default:
    assert (0);
  }

  old_buffer.buf_size = size_of_buffer;
  old_buffer.send_bytes = old_buffer.receive_bytes = 0;
  old_buffer.send_head_p = old_buffer.send_tail_p = old_buffer.send_buffer = 0;
  old_buffer.receive_head_p = old_buffer.receive_tail_p = 0;
  old_buffer.receive_buffer = 0;

  unsigned char *s_buf = (unsigned char *)malloc (size_of_buffer);
  unsigned char *r_buf = (unsigned char *)malloc (size_of_buffer);

  if (!r_buf || !s_buf)
  {
    free (r_buf);
    free (s_buf);
    status_val |= NO_MEMORY;
    return;
  }

  old_buffer.send_head_p = old_buffer.send_tail_p = 
    old_buffer.send_buffer = s_buf;
  old_buffer.receive_head_p = old_buffer.receive_tail_p = r_buf;
  old_buffer.receive_buffer = r_buf;

  port_init ();
  baud (baud_rate);
}
/*************************************************************************** 
Restore the previous interrupt, buffers, UART register values. 
September 17, 1989
****************************************************************************/
serial::~serial (void)
{
  if (status_val & (NO_MEMORY | NO_PORT))
    return;

  port_term ();

  free ((void *)old_buffer.receive_buffer);
  free ((void *)old_buffer.send_buffer);
}


#define I8259_COM1_MASK ((unsigned char)~(1 << 4))    /* IRQ4 */
#define I8259_COM2_MASK ((unsigned char)~(1 << 3))    /* IRQ3 */
#define I8259_END_OF_INTR_PORT 0x20
#define I8259_MASK_PORT 0x21

/* Interrupt enable bits. */
#define REC_DATA_INTR (1 << 0)
#define TRAN_DATA_INTR (1 << 1)
#define REC_STATUS_INTR (1 << 2)
#define MODEM_STATUS_INTR (1 << 3)

/* Interrupt ID defines. */
#define INTR_PENDING (1)      /* If this bit position is 0, then yes there */
                              /* is an interrupt pending. */
#define INTR_LINE_STATUS (6)  /* Overrun Error or Parity Error or */
                              /* Framing Error. */
#define INTR_REC_DATA (4)     /* Received data availiable. */
#define INTR_TRAN_EMPTY (2)   /* Transmit holding register is empty. */

#define LINE_CTRL_DATA (3)  /* Char length == 8, 1 stop bit, no parity, */

#define REC_REG (modem_port_addr + 0)
#define TRAN_REG (modem_port_addr + 0)
#define INTR_ENABLE_REG (modem_port_addr + 1)
#define INTR_IDENT_REG (modem_port_addr + 2)
#define LINE_CONTROL_REG (modem_port_addr + 3)
#define MODEM_CONTROL_REG (modem_port_addr + 4)
#define LINE_STATUS_REG (modem_port_addr + 5)
#define MODEM_STATUS_REG (modem_port_addr + 6)
#define SCRATCH_REG (modem_port_addr + 7)
#define DIVISOR_LS_REG (modem_port_addr + 0)
#define DIVISOR_MS_REG (modem_port_addr + 1)
#define DLAB (0x80)   /* Divisor Latch Access Bit */

#define MAGIC_BIT (8)   /* This is a bit for the modem Control Register */
                        /* that is used by IBM to enable interrupts, it */
                        /* is user defineable as far as the chip is */
                        /* concerned. */

#define DTR_BIT (1)     /* When set this sets the DTR line to a logic TRUE. */

/**********************************************************************
The serial port initialization routine.
**********************************************************************/
void serial::port_init (void)
{
  old_registers.line_cntr_reg = inp (LINE_CONTROL_REG);

  /* Test for the presence of a serial port. */
  /* Bit 7 must be set to a 0 to gain access to the INTR_ENABLE_REG. */
  /* Just some value... as long as bit 7 is 0 */
  outp (LINE_CONTROL_REG, 0x55);

  old_registers.intr_enable_reg = inp (INTR_ENABLE_REG);
  outp (INTR_ENABLE_REG, 0); /* Disable all the serial port interrupts. */

  if (inp (INTR_ENABLE_REG) != 0 || inp (LINE_CONTROL_REG) != 0x55)
  {
    // Restore the registers just in case.
    outp (LINE_CONTROL_REG, old_registers.line_cntr_reg);
    outp (INTR_ENABLE_REG, old_registers.intr_enable_reg);
    status_val = NO_PORT;
    return;
  }

  old_registers.modem_reg = inp (MODEM_CONTROL_REG);

  /* Enable access to the divisor latch. */
  outp (LINE_CONTROL_REG, old_registers.line_cntr_reg | DLAB);
  old_registers.divisor = (int) inp (DIVISOR_LS_REG);
  old_registers.divisor |= ((int) inp (DIVISOR_MS_REG)) << 8;
  outp (LINE_CONTROL_REG, LINE_CTRL_DATA);

  unsigned char enable_mask;

  switch (port)
  {
  case SERIAL_COM1:
    enable_mask = I8259_COM1_MASK;
    break;

  case SERIAL_COM2:
    enable_mask = I8259_COM2_MASK;
    break;

  default:
    assert (0);
  }

  enable_mask &= old_registers.enable_8259_mask = inp (I8259_MASK_PORT);

  // Swap bufffers, the new one is 'old_buffer'.  The old one is 
  // serial_buffers [port].  Its okay to swap because the serial port
  // interrupts have been disabled.

  struct serial_port_buffer temp_buf, *buf_p = &serial_buffers[port];
  temp_buf = *buf_p;
  *buf_p = old_buffer;
  old_buffer = temp_buf;

  status_val |= serial_port_init (&serial_buffers[port]);

  outp (LINE_STATUS_REG, 0);    // Clear all error flags.
  outp (MODEM_CONTROL_REG, MAGIC_BIT | DTR_BIT);

  // Enable both receive and transmit interrupts.
  outp (INTR_ENABLE_REG, TRAN_DATA_INTR | REC_DATA_INTR);
  outp (I8259_END_OF_INTR_PORT, serial_buffers[port].eoi_indicator);

  outp (I8259_MASK_PORT, enable_mask);
}
/****************************************************************************
Return 0 if the everything is okay.  Return ASCII string of error message if
there is a problem.  Like not enough memory for the buffers, what ever.
September 17, 1989
****************************************************************************/
const char *serial::status (void)
{
  char *ret_val = 0;

  if (status_val & NO_MEMORY)
    ret_val = "No memory for buffers.";
  else
  {
    if (status_val & NO_PORT)
      ret_val = "No serial port hardware.";
    else
    {
      if (status_val & NO_INTERRUPT)
        ret_val = "Unable to install interrupt service routine.";
    }
  }

  return ret_val;
}

/**********************************************************************
The serial port termination routine.
**********************************************************************/
void serial::port_term (void)
{
  outp (I8259_MASK_PORT, old_registers.enable_8259_mask);

  outp (INTR_ENABLE_REG, 0); /* Disable all the serial port interrupts. */

  // Restore the old interrupt. */
  serial_port_term (&serial_buffers [port]);

  // Swap buffers.
  struct serial_port_buffer temp_buf, *buf_p = &serial_buffers[port];
  temp_buf = *buf_p;
  *buf_p = old_buffer;
  old_buffer = temp_buf;

  outp (MODEM_CONTROL_REG, old_registers.modem_reg);

  /* Enable access to the divisor latch. */
  outp (LINE_CONTROL_REG, old_registers.line_cntr_reg | DLAB);

  outp (DIVISOR_LS_REG, old_registers.divisor);
  outp (DIVISOR_MS_REG, old_registers.divisor >> 8);

  outp (LINE_CONTROL_REG, old_registers.line_cntr_reg);
  outp (MODEM_CONTROL_REG, old_registers.modem_reg);

  outp (LINE_STATUS_REG, 0);    /* Clear all error flags. */
  outp (I8259_END_OF_INTR_PORT, old_buffer.eoi_indicator);
  outp (INTR_ENABLE_REG, old_registers.intr_enable_reg);
}

/****************************************************************************
Output a byte to the serial port.  Returns the number bytes in the output 
buffer after this byte is put in.
September 16, 1989
****************************************************************************/
unsigned int serial::put (unsigned char b)
{
  struct serial_port_buffer *p = &serial_buffers [port];

  // Wait for the buffer to have room.
  while (send_bytes_waiting() >= p->buf_size)
    ;

  *p->send_head_p++ = b;
  p->send_bytes++;

  // Enable transmit interrupts.
  outp (INTR_ENABLE_REG, inp(INTR_ENABLE_REG) | TRAN_DATA_INTR);

  if (p->send_head_p - p->send_buffer >= p->buf_size)
    p->send_head_p = p->send_buffer;

  return p->send_bytes;
}
/****************************************************************************
Input a byte from the serial port.  Returns the number of bytes in the input
buffer after this byte is taken out.  Returns ~0 if the input buffer was empty.
September 16, 1989
****************************************************************************/
unsigned int serial::get (unsigned char &b)
{
  struct serial_port_buffer *p = &serial_buffers [port];

  if (p->receive_bytes == 0)
    return ~0;

  b = *p->receive_tail_p++;
  if (p->receive_tail_p - p->receive_buffer >= p->buf_size)
    p->receive_tail_p = p->receive_buffer;

  return --(p->receive_bytes);
}

/****************************************************************************
Get the number of bytes remaining in the receive buffer.
September 16, 1989
****************************************************************************/
unsigned int serial::received_bytes_waiting(void)
{
  return serial_buffers[port].receive_bytes;
}

/****************************************************************************
Get the number of bytes remaining in the send buffer.
September 16, 1989
****************************************************************************/
unsigned int serial::send_bytes_waiting(void)
{
  return serial_buffers[port].send_bytes;
}

/****************************************************************************
Set the baud rate.
September 16, 1989
****************************************************************************/
void serial::baud (serial_baud b)
{
  unsigned char line_cntr_reg = inp (LINE_CONTROL_REG);

  /* Enable access to the divisor latch. */
  outp (LINE_CONTROL_REG, line_cntr_reg | DLAB);

  outp (DIVISOR_LS_REG, b & 0xFF);
  outp (DIVISOR_MS_REG, b >> 8);

  outp (LINE_CONTROL_REG, LINE_CTRL_DATA);
}

/****************************************************************************
Clear the receive buffer.  All data in the receive buffer is lost.
September 21, 1989
****************************************************************************/
void serial::receive_clear (void)
{
  unsigned char enable_reg = inp (INTR_ENABLE_REG);
  outp (INTR_ENABLE_REG, 0); // Disable all the serial port interrupts.

  struct serial_port_buffer *p = &serial_buffers [port];
  p->receive_bytes = 0;
  p->receive_head_p = p->receive_tail_p = p->receive_buffer;
  outp (INTR_ENABLE_REG, enable_reg); // Restore serial port interrupts.
}

/****************************************************************************
Clear the transmit buffer.  All data in the transmit buffer is lost.
September 21, 1989
****************************************************************************/
void serial::transmit_clear (void)
{
  unsigned char enable_reg = inp (INTR_ENABLE_REG);
  outp (INTR_ENABLE_REG, 0); // Disable all the serial port interrupts.

  struct serial_port_buffer *p = &serial_buffers [port];
  p->send_bytes = 0;
  p->send_head_p = p->send_tail_p = p->send_buffer;
  outp (INTR_ENABLE_REG, enable_reg); // Restore serial port interrupts.
}



