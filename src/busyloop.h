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
