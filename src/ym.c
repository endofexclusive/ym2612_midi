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

#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "ym.h"

/* These constants are part of the public interface. */
const uint8_t ym_PORT0 = 0x00;
const uint8_t ym_PORT1 = 0x01;

/* Because the structures are declared in static storage
(static or at file scope), they are initialized with all numeric
members zero and all pointers null. In dynamic storage, use
struct ym_control c  = {0}. */
static const struct ym_control CONTROL_RESET = {.A0 = 0, .A1 = 0,
  .NWR = 1, .NRD = 1, .NCS = 1, .NIC = 0};
static const struct ym_control CONTROL_IDLE = {.A0 = 0, .A1 = 0,
  .NWR = 1, .NRD = 1, .NCS = 1, .NIC = 1};
static const struct ym_control CONTROL_WRITE = {.A0 = 0, .A1 = 0,
  .NWR = 0, .NRD = 1, .NCS = 0, .NIC = 1};
static const uint8_t ym_A0_ADDRESS = 0x00;
static const uint8_t ym_A0_DATA = 0x01;

static uint8_t ym_get_offset(uint8_t channel, uint8_t operator)
{
    /* Failing early or late is a matter of design. */
    assert(operator <= 3);
    assert(channel <= 5);
    return operator * 4 + channel % 3;
}

static uint8_t ym_get_port(uint8_t channel)
{
    assert(channel <= 5);
    return channel / 3;
}

void ym_init(Ym_driver *self, ym_set_control *set_control,
  ym_set_data *set_data, ym_delay_us *delay_us)
{
    /* Make sure that not both MCU and chip activates their
    output. */
    self->set_control = set_control;
    self->set_data = set_data;
    self->delay_us = delay_us;
}

void ym_reset(Ym_driver *self)
{
    self->set_control(CONTROL_RESET);
    /* Sleep for 192 cycles, equals 24 us @ 8MHz. This is the
    reset pulse width. */
    self->delay_us(24);
    self->set_control(CONTROL_IDLE);
    /* FIXME: Use a macro for number of elements */
    int i = sizeof(self->shadow_0x30) / sizeof(uint8_t);
    while(i--)
    {
        self->shadow_0x30[i] = 0;
    }
}
/* FIXME: The parameter types... */
static void ym_write_lowlevel(Ym_driver *self, uint8_t a0,
  uint8_t a1, uint8_t d)
{
    /* FIXME: The variable name this_control sucks. */
    struct ym_control this_control = CONTROL_WRITE;
    this_control.A0 = a0;
    this_control.A1 = a1;
    self->set_data(d);
    self->set_control(this_control);
    self->delay_us(1);
    this_control.NCS = 1;
    self->set_control(this_control);
}

/* According to translated documentation, wait 17 cycles (2 us)
after write of address and wait 83 cycles (10 us) after write
of data (8MHz). */

void ym_set(Ym_driver *self, uint8_t port, uint8_t reg,
  uint8_t value)
{
    /* Assert the user input (but not internal stuff). */
    assert(ym_PORT0 == port || ym_PORT1 == port);
    /* Assert reg. */

    /* Select register. */
    ym_write_lowlevel(self, ym_A0_ADDRESS, port, reg);
    /* Wait for write to settle. */
    self->delay_us(2);

    /* Write data to current register. */
    ym_write_lowlevel(self, ym_A0_DATA, port, value);
    /* Wait for write to settle. */
    self->delay_us(10);
}

void ym_key_on(Ym_driver *self, uint8_t channel)
{
    assert(channel <= 5);
    ym_set(self, ym_PORT0, 0x28, 0xf0 + channel);
}

void ym_key_off(Ym_driver *self, uint8_t channel)
{
    assert(channel <= 5);
    ym_set(self, ym_PORT0, 0x28, 0x00 + channel);
}

void ym_set_multiplier(Ym_driver *self, uint8_t channel,
  uint8_t operator, uint8_t multiplier)
{
    uint8_t port, *shadowp, offset;

    assert(multiplier <= 0x0f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow_0x30 + offset;
    *shadowp = (*shadowp & 0xf0) + multiplier;
    ym_set(self, port, 0x30 + offset, *shadowp) ;
}

void ym_set_detune(Ym_driver *self, uint8_t channel,
  uint8_t operator, uint8_t detune)
{
    uint8_t port, *shadowp, offset;

    assert(detune <= 0x07);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow_0x30 + offset;
    *shadowp = (*shadowp & 0x8f) + (detune << 4);
    ym_set(self, port, 0x30 + offset, *shadowp);
}

void ym_set_amplitude(Ym_driver *self, uint8_t channel,
  uint8_t operator, uint8_t amplitude)
{
    uint8_t port, offset;

    assert(amplitude <= 0x7f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    ym_set(self, port, 0x40 + offset, amplitude);
}
