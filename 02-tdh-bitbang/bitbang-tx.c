                                                       /* Bitbang Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

void baud_delay() {
  _delay_us(104.17); /* 1/9600 * 1000 * 1000 */
}

void send_byte(unsigned char c) {
    PORTB = 0b00000000; /* start bit */ baud_delay();
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001000 : 0b00000000; baud_delay(); c = c >> 1;
    PORTB = 0b00001000; /* stop bit */  baud_delay();
}

int main(void) {

  // -------- Inits --------- //
  DDRB |= 0b00001000;
  PORTB = 0b00001000;
  int i = 0;

  // ------ Event loop ------ //
  while (1) {

    _delay_ms(1000);                                           /* wait */
    send_byte('a'+(i++%10));
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
