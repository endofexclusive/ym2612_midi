#include "busyloop.h"

void busyloop_delay_us(uint16_t delay)
{
    TCCR0 |= _BV(WGM01) + _BV(CS00);
    OCR0 = 79;
    TCNT0 = 0;
    delay = (delay / 10) + 1;

    while(delay)
    {
        TIFR |= _BV(OCF0);
        while (bit_is_clear(TIFR, OCF0));
        delay--;
    }
}

void busyloop_delay_ms(uint16_t delay)
{
    /* The values in this function are tuned for 8Mhz system
    clock. */
    /* Timer/Counter Control Register: prescaler clk_IO/64
    Clear Time on Compare (CTC) mode */
    TCCR0 |= _BV(WGM01) + _BV(CS01) + _BV(CS00);
    /* Output Compare Register. T = (N(1+OCR0)) / f_IO */
    OCR0 = 124;
    /* Timer/Counter 0: TCNT0 increases until a compare match
    occurs between TCNT0 and OCR0, and then TCNT0 is cleared. */
    TCNT0 = 0;

    while(delay)
    {
        /* Clear the Output Compare Flag in the Timer Interrupt
        Flag Register */
        TIFR |= _BV(OCF0);
        while (bit_is_clear(TIFR, OCF0));
        delay--;
    }
}
