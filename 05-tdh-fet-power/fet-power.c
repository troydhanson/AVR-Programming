#include <avr/io.h>

int main(void) {

  DDRB  = 0b00001110; /* output on pins PB3, PB2, and PB1 */
  PORTB = 0b00010001; /* enable pull up on button pins PB4, PB0 */

  while (1) {

     /* set the "press detected" LED on PB3, if button on PB4 is pressed */
     if ((PINB & 0b00010000) == 0) PORTB |= 0b00001000; else PORTB &= 0b11110111;

     /* drive the FET gate (PB1) and LED (PB2) when button (PB0) down */
    if ((PINB & 0b00000001) == 0) PORTB |= 0b00000110; else PORTB &= 0b11111001;
  }

  return 0;
}
