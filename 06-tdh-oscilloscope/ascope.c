// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "limits.h"
#include "USART.h"

#define MAX_SIGNAL_HZ 120
#define SIGNAL_PERIOD (1.0 / MAX_SIGNAL_HZ)     /* seconds for one cycle */
#define SAMPLES_PER_SEC (MAX_SIGNAL_HZ * 2)     /* Nyquist wants 2x hz */
#define SAMPLE_INTERVAL (1.0 / SAMPLES_PER_SEC) /* seconds between samples */

/* sanity check:
 * ensure sample rate can be sent at the USART speed 
 */
#define USART_SPEED_BPS 9600  /* ensure this matches ADC setup below */
#define USART_SPEED_BYTES_PER_SEC (USART_SPEED_BPS / 8)
#if SAMPLES_PER_SEC > USART_SPEED_BYTES_PER_SEC
#error "sample rate exceeds serial output speed"
#endif

// -------- Functions --------- //
static inline void initFreerunningADC(void) {
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);    /* ADC clock prescaler /8 */
  ADMUX |= (1 << ADLAR);     /* left-adjust result, return only 8 bits */
  ADCSRA |= (1 << ADEN);                                 /* enable ADC */
  ADCSRA |= (1 << ADATE);                       /* auto-trigger enable */
  ADCSRA |= (1 << ADSC);                     /* start first conversion */
}

/* recent sample buffer to find recent min/max */
#define NSAMPLES (SAMPLES_PER_SEC * 2)
char samples[NSAMPLES];
unsigned n=0;
int above_midpoint; /* whether last sample was above (max-min)/2 */
char min, max;

void find_extremes() {
  min = SCHAR_MAX; /* set to opposite extreme initially */
  max = SCHAR_MIN; /* same */
  unsigned i;
  for(i=0; i < NSAMPLES; i++) {
    if (samples[i] > max) max = samples[i];
    if (samples[i] < min) min = samples[i];
  }
}

int cross_midpoint(char sample) {
  char mid = (max - min) / 2;
  if ((sample > mid) && above_midpoint) return 0;
  if ((sample <= mid) && !above_midpoint) return 0;
  above_midpoint = (sample > mid) ? 1 : 0;
  return 1;
}

void toggle_speaker() {
}


int main(void) {
  initUSART();
  initFreerunningADC();
  while (1) {
    char sample = ADCH;       /* obtain sample from ADC */
    samples[n++] = sample;    /* store sample in our buffer */
    if (n == NSAMPLES) n=0;
    transmitByte(sample);     /* transmit the high byte, left-adjusted */

    /* find min,max in nsamples. we don't worry about the fact that the 
     * buffer is initially empty. it fills up in seconds. 
     */
     find_extremes();
     if (cross_midpoint(sample)) toggle_speaker(); /* match hz of signal */
    _delay_ms(SAMPLE_INTERVAL);
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
