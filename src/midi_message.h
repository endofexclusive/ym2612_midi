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

#ifndef MIDI_MESSAGE_H
#define MIDI_MESSAGE_H
/** @file
MIDI message container and manipulation.
@author Martin Åberg martin@fripost.org
*/

#include <stdint.h>
#include <stdbool.h>

typedef struct Midi_message Midi_message;

struct Midi_message {
    uint8_t status;
    uint8_t data1, data2;
};

bool midi_message_is_note_off(Midi_message *m);
bool midi_message_is_note_on(Midi_message *m);
bool midi_message_is_control(Midi_message *m);
bool midi_message_is_program_change(Midi_message *m);
bool midi_message_is_mode(Midi_message *m);

#endif
