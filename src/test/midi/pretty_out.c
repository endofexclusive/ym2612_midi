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

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "pretty_out.h"

static void pretty_out_put(Pretty_out *self, Midi_message *m)
{
    printf("%3d:  ", self->count);
    if (midi_message_is_note_on(m)) {
        printf("Note-On, channel %x, key %x, vel %x\n",
          m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_note_off(m)) {
        printf("Note-Off, channel %x, key %x, vel %x\n",
          m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_control(m)) {
        printf("Control change, channel %x, #%x, value %x\n",
          m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_mode(m)) {
        printf("Channel mode, channel %x, #%x, value %x\n",
          m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_program_change(m)) {
        printf("Program change, channel %x, program %x\n",
          m->status & 0x0f, m->data1);
    } else {
        printf("Unknown MIDI message [%x, %x, %x].\n", 
          m->status, m->data1, m->data2);
    }
    
    self->count++;
}

void pretty_out_init(Pretty_out *self)
{
    Midi_out *m_out = &(self->parent);
    m_out->put = (Midi_out_put *) pretty_out_put;
    self->count = 0;
    dputs("Initializing pretty out");
}
