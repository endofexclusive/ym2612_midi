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

#include "debug.h"
#include "ym_midi.h"
#include "ym.h"

typedef void cc_function(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value);

struct cc_function_node {
    cc_function *fun;
    uint8_t upper;
    uint8_t lower;
};

static uint8_t scale(uint8_t n)
{
    return 128/n;
}

static uint8_t get_operator(uint8_t controller)
{
    return controller % 4;
}

static void cc_channel_algorithm(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
//    ym_set_algorithm(driver, channel, value/scale(8));
}

static void cc_operator_1_self_feedback(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
//    ym_set_op1_self_feedback(driver, channel, value/scale(8));
}

static void cc_channel_pan(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
//    ym_set_pan(driver, channel, value/scale(3));
}

static void cc_channel_lfo_am_sensitivity(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_channel_lfo_fm_sensitivity(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_lfo_frequency(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_channel_36_mode(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_amplitude(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
    ym_set_amplitude(driver, channel, get_operator(controller),
      value/scale(128));
}

static void cc_operator_attack_rate(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_d1r(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_d1l(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_d2r(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_rr(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_am(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_rate_scaling(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
}

static void cc_operator_freq_multiplier(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
    ym_set_multiplier(driver, channel, get_operator(controller),
      value/scale(16));
}

static void cc_operator_freq_detune(Ym_driver *driver, uint8_t controller,
  uint8_t channel, uint8_t value)
{
    ym_set_detune(driver, channel, get_operator(controller),
      value/scale(8));
}

/*
                ym_set_attack_rate(driver, channel, operator,
                  value/scale(32));
                ym_set_d1r(driver, channel, operator,
                  value/scale(32));
                ym_set_d1l(driver, channel, operator,
                  value/scale(16));
                ym_set_d2r(driver, channel, operator,
                  value/scale(32));
                ym_set_rr(driver, channel, operator,
                  value/scale(16));
                ym_set_am(driver, channel, operator, 0 != value);
                ym_set_rate_scaling(driver, channel, operator,
                  value/scale(4));
*/

#include "ym_midi_cc.c"

#define NELEMENTS(a) (sizeof(a) / sizeof(*(a)))

/* Implementation of "MIDI Implementation Chart v 2.0, Control
Number Information". The function has no channel guard. */
static void ym_midi_put_cc(Ym_midi *self, Midi_message *m)
{
    struct cc_function_node *node = cc_functions;
    uint8_t i = NELEMENTS(cc_functions);
    const uint8_t cc = m->data1;
    const uint8_t channel = m->status & 0x0f;

    while (i--) {
        if (node->upper <= cc && node->lower <= cc) {
            node->fun(self->driver, cc, channel, m->data2);
            break;
        }
        node++;
    }
}


static void ym_midi_put(Ym_midi *self, Midi_message *m)
{
    uint8_t channel;

    channel = m->status & 0x0f;
    if (5 < channel) {
        dputs("5 < channel, skip");
        return;
    }
    if (midi_message_is_note_on(m)) {
        dprint("Note-On, channel %x, key %x, vel %x\n",
          m->status & 0x0f, m->data1, m->data2);
        ym_key_on(self->driver, channel);
    } else if (midi_message_is_note_off(m)) {
        dprint("Note-Off, channel %x, key %x, vel %x\n",
          m->status & 0x0f, m->data1, m->data2);
        ym_key_off(self->driver, channel);
    } else if (midi_message_is_control(m)) {
        dprint("Control change, channel %x, #%x, value %x\n",
          m->status & 0x0f, m->data1, m->data2);
        ym_midi_put_cc(self, m);
    } else if (midi_message_is_mode(m)) {
        dprint("Channel mode, channel %x, #%x, value %x\n",
          m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_program_change(m)) {
        dprint("Program change, channel %x, program %x\n",
          m->status & 0x0f, m->data1);
    } else {
        dprint("Unimplemented MIDI message [%x, %x, %x], skip.\n", 
          m->status, m->data1, m->data2);
    }
}

void ym_midi_init(Ym_midi *self, Ym_driver *driver)
{
    Midi_out *m_out = &(self->parent);
    m_out->put = (Midi_out_put *) ym_midi_put;
    self->driver = driver;
    dputs("Initializing Ym_midi");
}

