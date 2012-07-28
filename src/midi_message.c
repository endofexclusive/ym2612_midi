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

#include "midi_message.h"

bool midi_message_is_note_off(Midi_message *m)
{
    if (0x80 == (m->status & 0xf0)) {
        return true;
    }
    if (0x90 == (m->status & 0xf0)) {
        if (m->data2 == 0x00) {
            return true;
        }
    }
    return false;
}

bool midi_message_is_note_on(Midi_message *m)
{
    if (0x90 == (m->status & 0xf0)) {
        if (m->data2 != 0x00) {
            return true;
        }
    }
    return false;
}

bool midi_message_is_control(Midi_message *m)
{
    if (0xb0 == (m->status & 0xf0)) {
        if (m->data1 <= 119) {
            return true;
        }
    }
    return false;
}

bool midi_message_is_mode(Midi_message *m)
{
    if (0xb0 == (m->status & 0xf0)) {
        if (120 <= m->data1) {
            return true;
        }
    }
    return false;
}

bool midi_message_is_program_change(Midi_message *m)
{
    return (0xc0 == (m->status & 0xf0)) ? true : false;
}

