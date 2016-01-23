                                                       /* Bitbang Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

void baud_delay() {
  _delay_us(104.17); /* 1/9600 * 1000 * 1000 */
}

void send_byte(unsigned char c) {
    PORTB = 0b00000100; /* start bit */ baud_delay();
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = (c & 1) ? 0b00001100 : 0b00000100; baud_delay(); c = c >> 1;
    PORTB = 0b00001100; /* stop bit */  baud_delay();
}

unsigned char read_byte() {
    unsigned char b=0;
    while (PINB & 0b00000100) {}; /* wait for start bit */ baud_delay();
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); b = b >> 1U;
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); b = b >> 1U;
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); b = b >> 1U;
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); b = b >> 1U;
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); b = b >> 1U;
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); b = b >> 1U;
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); b = b >> 1U;
    b |=  (PINB & 0b00000100 ) ?  128 : 0; baud_delay(); /* ignore stop bit */
    return b;
}

int main(void) {
  unsigned char b;

  // -------- Inits --------- //
  DDRB  = 0b00001000; /* tx on pin 3, rx on pin 2 */
  PORTB = 0b00001100; /* tx pin high (quiescent), rx pull up */

  // ------ Event loop ------ //
  while (1) {
    b = read_byte();
    send_byte(b); /* echo the byte back */
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
