#ifndef BUSYLOOP_H
#define BUSYLOOP_H
/** @file
Busy-waiting-loop module for ATmega16. This module is fine-tuned
for a system clock frequency of 8 MHz. Timer/Counter0 is used.
@author Martin Åberg martin@fripost.org
*/

#include <avr/io.h>

/** Delay execution for a specified @e number of
milliseconds. */
void busyloop_delay_ms(uint16_t number);
/** Delay execution for a specified @e number of
microseconds. */
void busyloop_delay_us(uint16_t number);

#endif /* BUSYLOOP_H */
