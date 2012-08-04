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

#ifndef YM_H
#define YM_H

#include <inttypes.h>

/* Driver for the YM2612 chip.  fixme: Add const qualifiers to
function parameters where suitable. Define types. That will
prevent bugs that appear because functions are called with
parameters in wrong order.
*/

struct ym_control;

typedef struct Ym_driver Ym_driver;

/* Set the control signals on the YM chip.
control: Filled in by the driver before call. */
typedef void (ym_set_control)(struct ym_control control);

/* Write to the 8-bit bidrectional data bus.
data: The data to write.
*/
typedef void (ym_set_data)(uint8_t data);

/* Delay the execution for a given number of microseconds.
time: The number of microseconds to delay.
*/
typedef void (ym_delay_us)(uint16_t time);

/* Chip input pins. */
struct ym_control {
    /* Select address or data mode. */
    unsigned int A0 : 1;
    /* Port selection. */
    unsigned int A1 : 1;
    /* Write mode on data bus. */
    unsigned int NWR : 1;
    /* Read mode on data bus. */
    unsigned int NRD : 1;
    /* Chip select. */
    unsigned int NCS : 1;
    /* Initialize registers. */
    unsigned int NIC : 1;
};

struct Ym_driver {
    ym_set_control *set_control;
    ym_set_data *set_data;
    ym_delay_us *delay_us; 
    uint8_t shadow_0x30[0x10];
};

/* Identifies port 0.
fixme: Represent this value as an enum.
*/
extern const uint8_t ym_PORT0;
/* Identifies port 1. */
extern const uint8_t ym_PORT1;

/* Write a value to a chip register.
port: This is ym_PORT0 or ym_PORT1.
reg: The YM register to write to.
value: The value that will be written.
*/
void ym_set(Ym_driver *self, uint8_t port, uint8_t reg,
  uint8_t value);

/* Initialize the driver. After the driver has been initialized,
ym_reset() should be called by the user to perform a chip
reset. Hardware access functions are supplied by the user.
*/

void ym_init(Ym_driver *self, ym_set_control *set_control,
  ym_set_data *set_data, ym_delay_us *delay_us);

/* Perform chip hardware reset.
Prerequirement: The driver has been initialized by ym_init().
Postrequirement: All chip registers and shadow registers are
set to zero.
*/
void ym_reset(Ym_driver *self);

/* Play a note on a channel. */
void ym_key_off(Ym_driver *self, uint8_t channel);

/* Stop playing a note on a channel. */
void ym_key_on(Ym_driver *self, uint8_t channel);

void ym_set_algorithm(Ym_driver *self, uint8_t channel,
  uint8_t algorithm);

void ym_set_op1_self_feedback(Ym_driver *self, uint8_t channel,
  uint8_t feedback);

void ym_set_pan(Ym_driver *self, uint8_t channel,
  uint8_t pan);

/* Set the frequency multiplier of a channel operator. */
void ym_set_multiplier(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t multiplier);

/* Set the frequency detune factor for a channel operator.
fixme: This function has to be tested.
*/
void ym_set_detune(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t detune);

/* Set the amplitude of an operator. */
void ym_set_amplitude(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t amplitude);

#endif
