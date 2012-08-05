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
#include "debug.h"

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
    int i = sizeof(self->shadow) / sizeof(uint8_t);
    while(i--)
    {
        self->shadow[0][i] = 0;
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
    /* fixme: Assert reg. */

    dprint("port%d:$%02x <- $%02x\n", port, reg, value);

    /* Select register. */
    ym_write_lowlevel(self, ym_A0_ADDRESS, port, reg);
    /* Wait for write to settle. */
    self->delay_us(2);

    /* Write data to current register. */
    ym_write_lowlevel(self, ym_A0_DATA, port, value);
    /* Wait for write to settle. */
    self->delay_us(10);
}

/* This is the F-Number table for "Note" C# to C. */
static uint16_t notes[] = {
    654, 693, 734, 778, 824, 873, 925, 980, 1038, 1100,
    1165, 1235
};

/* Key ranges from 0 to 8*12-1. */
void ym_key_on(Ym_driver *self, uint8_t channel, uint8_t key)
{
    uint8_t port, offset, block, msb, lsb;

    assert(channel <= 5);
    assert(key <= 95);

    port = ym_get_port(channel);
    offset = channel % 3;

    block = key / 12;
    key = key % 12;
    lsb = notes[key] % 256;
    msb = notes[key] >> 8;
    ym_set(self, port, 0xa4 + offset, (block << 3) + msb);
    ym_set(self, port, 0xa0 + offset, lsb);

    ym_set(self, port, 0x28, 0xf0 + channel);
}

void ym_key_off(Ym_driver *self, uint8_t channel)
{
    assert(channel <= 5);

    ym_set(self, ym_get_port(channel), 0x28, 0x00 + channel);
}


void ym_set_algorithm(Ym_driver *self, uint8_t channel,
  uint8_t algorithm)
{
    uint8_t port, *shadowp, offset;

    assert(algorithm <= 0x07);
    assert(channel <= 5);

    port = ym_get_port(channel);
    offset = channel % 3;
    shadowp = self->shadow[port] + SHADOWB0 + offset;
    *shadowp = (*shadowp & 0xf8) + algorithm;
    ym_set(self, port, 0xb0 + offset, *shadowp) ;
}

void ym_set_feedback(Ym_driver *self, uint8_t channel,
  uint8_t feedback)
{
    uint8_t port, *shadowp, offset;

    assert(feedback <= 0x07);
    assert(channel <= 5);

    port = ym_get_port(channel);
    offset = channel % 3;
    shadowp = self->shadow[port] + SHADOWB0 + offset;
    *shadowp = (*shadowp & 0xc7) + (feedback << 3);
    ym_set(self, port, 0xb0 + offset, *shadowp) ;
}

void ym_set_lr(Ym_driver *self, uint8_t channel,
  uint8_t lr)
{
    uint8_t port, *shadowp, offset;

    assert(lr <= 0x03);
    assert(channel <= 5);

    port = ym_get_port(channel);
    offset = channel % 3;
    shadowp = self->shadow[port] + SHADOWB4 + offset;
    *shadowp = (*shadowp & 0xc7) + (lr << 6);
    ym_set(self, port, 0xb4 + offset, *shadowp) ;
}

/*
void ym_set_ch36_special_mode(Ym_driver *self, uint8_t channel, uint8_t mode)
{
}
*/


void ym_set_multiple(Ym_driver *self, uint8_t channel,
  uint8_t operator, uint8_t multiplier)
{
    uint8_t port, *shadowp, offset;

    assert(multiplier <= 0x0f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow[port] + SHADOW30 + offset;
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
    shadowp = self->shadow[port] + SHADOW30 + offset;
    *shadowp = (*shadowp & 0x8f) + (detune << 4);
    ym_set(self, port, 0x30 + offset, *shadowp);
}


void ym_set_total_level(Ym_driver *self, uint8_t channel,
  uint8_t operator, uint8_t level)
{
    uint8_t port, offset;

    assert(level <= 0x7f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    ym_set(self, port, 0x40 + offset, level);
}

void ym_set_attack_rate(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t rate)
{
    uint8_t port, *shadowp, offset;

    assert(rate <= 0x1f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow[port] + SHADOW50 + offset;
    *shadowp = (*shadowp & 0xe0) + rate;
    ym_set(self, port, 0x50 + offset, *shadowp) ;
}

void ym_set_decay_rate(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t rate)
{
    uint8_t port, *shadowp, offset;

    assert(rate <= 0x1f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow[port] + SHADOW60 + offset;
    *shadowp = (*shadowp & 0xe0) + rate;
    ym_set(self, port, 0x60 + offset, *shadowp) ;
}

void ym_set_sustain_level(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t level)
{
    uint8_t port, *shadowp, offset;

    assert(level <= 0x0f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow[port] + SHADOW80 + offset;
    *shadowp = (*shadowp & 0x0f) + (level << 4);
    ym_set(self, port, 0x80 + offset, *shadowp);
}

void ym_set_sustain_rate(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t rate)
{
    uint8_t port, offset;

    assert(rate <= 0x1f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    ym_set(self, port, 0x70 + offset, rate);
}

void ym_set_release_rate(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t rate)
{
    uint8_t port, *shadowp, offset;

    assert(rate <= 0x0f);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow[port] + SHADOW80 + offset;
    *shadowp = (*shadowp & 0xf0) + rate;
    ym_set(self, port, 0x80 + offset, *shadowp) ;
}

void ym_set_key_scale(Ym_driver *self, uint8_t channel, uint8_t operator,
  uint8_t scale)
{
    uint8_t port, *shadowp, offset;

    assert(scale <= 0x03);

    port = ym_get_port(channel);
    offset = ym_get_offset(channel, operator);
    shadowp = self->shadow[port] + SHADOW50 + offset;
    *shadowp = (*shadowp & 0x3f) + (scale << 6);
    ym_set(self, port, 0x50 + offset, *shadowp);
}
