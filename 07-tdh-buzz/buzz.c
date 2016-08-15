// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "limits.h"
#include "USART.h"

void toggle_speaker() {
  PORTD ^= (1 << PD6);
}

void init_tdh() {
  DDRD |= (1 << PD6); /* set speaker pin as OUTPUT */
  DDRD |= (1 << PD1); /* set serial TX pin as OUTPUT */
}

int main(void) {
  int freq = 60; /* cycles/second */
  int period_ms = 1000.0/freq; /* milliseconds per cycle */

  init_tdh();
  initUSART();

  while (1) {
    toggle_speaker(); /* match hz of signal */
    _delay_ms(period_ms/2);
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}


