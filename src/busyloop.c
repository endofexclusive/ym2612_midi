/* Copyright (C) 2012 Martin Åberg

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program (COPYING).  If not, see <http://www.gnu.org/licenses/>. */

#include "busyloop.h"

/* The values are tuned for an 8Mhz system clock. */

/* Output Compare Register. T = N(1+OCR0) / f */
#define TIMER0_OUTPUT_COMPARE_REGISTER_MS 124
#define TIMER0_OUTPUT_COMPARE_REGISTER_US 79

/* Timer/Counter Control Register: prescaler f/64 */
#define TIMER0_CLOCK_SOURCE_MS (_BV(CS01) + _BV(CS00))
/* Timer/Counter Control Register: prescaler f/1 */
#define TIMER0_CLOCK_SOURCE_US (_BV(CS00))

void busyloop_delay_ms(uint16_t delay)
{
    /* Clear Time on Compare (CTC) mode */
    TCCR0 |= _BV(WGM01) + TIMER0_CLOCK_SOURCE_MS;
    OCR0 = TIMER0_OUTPUT_COMPARE_REGISTER_MS;
    /* Timer/Counter 0: TCNT0 increases until a compare match
    occurs between TCNT0 and OCR0, and then TCNT0 is cleared. */
    TCNT0 = 0;

    while(delay) {
        /* Clear the Output Compare Flag in the Timer Interrupt
        Flag Register. */
        TIFR |= _BV(OCF0);
        while (bit_is_clear(TIFR, OCF0));
        delay--;
    }
}

void busyloop_delay_us(uint16_t delay)
{
    TCCR0 |= _BV(WGM01) + TIMER0_CLOCK_SOURCE_US;
    OCR0 = TIMER0_OUTPUT_COMPARE_REGISTER_US;
    TCNT0 = 0;
    delay = (delay / 10) + 1;

    while(delay) {
        TIFR |= _BV(OCF0);
        while (bit_is_clear(TIFR, OCF0));
        delay--;
    }
}
