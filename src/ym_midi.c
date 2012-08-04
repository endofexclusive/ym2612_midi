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

#define CC_SET_ALGORITHM 3
#define CC_SET_OP1_SELF_FEEDBACK 9
#define CC_SET_PAN 10
#define CC_SET_LFO_AM_SENSITIVITY 14
#define CC_SET_LFO_FM_SENSITIVITY 15
#define CC_SET_LFO_FREQUENCY 16
#define CC_SET_CHANNEL36_MODE 17
#define CC_SET_AMPLITUDE 20
#define CC_SET_ATTACK_RATE 24
#define CC_SET_D1R 28
#define CC_SET_D1L 52
#define CC_SET_D2R 56
#define CC_SET_RR 60
#define CC_SET_AM 104
#define CC_SET_RATE_SCALING 108
#define CC_SET_MULTIPLIER 112
#define CC_SET_DETUNE 116

static uint8_t scale(uint8_t n)
{
    return 128/n;
}

/* Implementation of "MIDI Implementation Chart v 2.0, Control
Number Information". A lookup-table based approach has been
considered but the focus for now is on saving data memory
(not code memory). The function has no channel guard. */
static void ym_midi_put_cc(Ym_midi *self, Midi_message *m)
{
    const uint8_t channel = m->status & 0x0f;
    const uint8_t controller = m->data1;
    const uint8_t value = m->data2;
    Ym_driver *driver = self->driver;

    switch (controller) {
    case CC_SET_ALGORITHM:
        ym_set_algorithm(driver, channel, value/scale(8));
        break;
    case CC_SET_OP1_SELF_FEEDBACK:
        ym_set_op1_self_feedback(driver, channel, value/scale(8));
        break;
    case CC_SET_PAN:
        ym_set_pan(driver, channel, value/scale(3));
        break;
    case CC_SET_LFO_AM_SENSITIVITY:
    case CC_SET_LFO_FM_SENSITIVITY:
    case CC_SET_LFO_FREQUENCY:
    case CC_SET_CHANNEL36_MODE:
        break;
    default:
        {
            /* These assignments depend on the layout of CC the
            numbers. */
            uint8_t operator = controller / 4;
            uint8_t function = controller - operator;

            switch (function) {
            case 20:
                ym_set_amplitude(driver, channel, operator,
                  value/scale(128));
                break;
            case 24:
                ym_set_attack_rate(driver, channel, operator,
                  value/scale(32));
                break;
            case 28:
                ym_set_d1r(driver, channel, operator,
                  value/scale(32));
                break;
            case 52:
                ym_set_d1l(driver, channel, operator,
                  value/scale(16));
                break;
            case 56:
                ym_set_d2r(driver, channel, operator,
                  value/scale(32));
                break;
            case 60:
                ym_set_rr(driver, channel, operator,
                  value/scale(16));
                break;
            case 104:
                ym_set_am(driver, channel, operator, 0 != value);
                break;
            case 108:
                ym_set_rate_scaling(driver, channel, operator,
                  value/scale(4));
                break;
            case 112:
                ym_set_multiplier(driver, channel, operator,
                  value/scale(16));
                break;
            case 116:
                ym_set_detune(driver, channel, operator,
                  value/scale(8));
                break;
            }
        }
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
