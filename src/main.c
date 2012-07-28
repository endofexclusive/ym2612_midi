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

#include <avr/io.h>
#include <stdlib.h>
#include <assert.h>
#include "ym.h"
#include "busyloop.h"

/* This test file assumes the following pin configuration.
PA0: NCS PA1: NWR PA2: NRD PA3: A0 PA4: A1 PA5: NIC */

void my_control(struct ym_control);
void my_data(uint8_t);
void my_io_init(void);

struct ym_config my_config = {my_control, my_data, busyloop_delay_us};

void ym_preset_basic(void);
int main(void)
{
    busyloop_delay_ms(1000);
    my_io_init();
    ym_init(&my_config);
    ym_reset();
    ym_preset_basic();
    while(1)
    {
        ym_key_on(0);
        busyloop_delay_ms(300);
        ym_key_off(0);
        busyloop_delay_ms(200);
    }
    return 0;
}
/*
"Implementation chart"
 Key on/off (on: 0xf0...0xf5, off: 0x00...0x05)
 Algorithm
 Operators
  Volume, ADSR
  Waveform
  Multiplier
*/

void ym_preset_basic(void)
{
    ym_set(ym_PORT0, 0x40,     0x7f);
    ym_set(ym_PORT0, 0x44,     0x7f);
    ym_set(ym_PORT0, 0x48,     0x7f);
    ym_set(ym_PORT0, 0x4C,     0x7f);
    ym_set(ym_PORT0, 0x50,     0x5F);//     RS/AR
    ym_set(ym_PORT0, 0x54,     0x99);
    ym_set(ym_PORT0, 0x58,     0x5F);
    ym_set(ym_PORT0, 0x5C,     0x94);
    ym_set(ym_PORT0, 0x60,     0x5);//   AM/D1R
    ym_set(ym_PORT0, 0x64,     0x5);
    ym_set(ym_PORT0, 0x68,     0x5);
    ym_set(ym_PORT0, 0x6C,     0x7);
    ym_set(ym_PORT0, 0x70,     0x2);//  D2R
    ym_set(ym_PORT0, 0x74,     0x2);
    ym_set(ym_PORT0, 0x78,     0x2);
    ym_set(ym_PORT0, 0x7C,     0x2);
    ym_set(ym_PORT0, 0x80,     0x11);//    D1L/RR
    ym_set(ym_PORT0, 0x84,     0x11);
    ym_set(ym_PORT0, 0x88,     0x11);
    ym_set(ym_PORT0, 0x8C,     0xA6);
    ym_set(ym_PORT0, 0xB0,     0x7);//     Feedback/algorithm
    ym_set(ym_PORT0, 0xB4,     0xC0);//     Both speakers on
    ym_set(ym_PORT0, 0xA4,     0x22);//     Set frequency
    ym_set(ym_PORT0, 0xA0,     0x69);
}

void my_io_init(void)
{
    /* Configure the control lines as output pins. */
    DDRA = _BV(DDA0) + _BV(DDA1) + _BV(DDA2) + _BV(DDA3) +
      _BV(DDA4) + _BV(DDA5);
    /* Configure the data lines as output pins. */
    DDRB = _BV(DDB0) + _BV(DDB1) + _BV(DDB2) + _BV(DDB3) +
      _BV(DDB4) + _BV(DDB5) + _BV(DDB6) + _BV(DDB7);
}

void my_control(struct ym_control control)
{
    uint8_t target;

    target = 0;
    if (control.A0)
        target |= _BV(PA3);
    if (control.A1)
        target |= _BV(PA4);
    if (control.NWR)
        target |= _BV(PA1);
    if (control.NRD)
        target |= _BV(PA2);
    if (control.NCS)
        target |= _BV(PA0);
    if (control.NIC)
        target |= _BV(PA5);
    PORTA = target;
}

void my_data(uint8_t data)
{
    PORTB = data;
}

