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
