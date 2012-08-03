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

#ifndef MIDI_H
#define MIDI_H

#include <stdbool.h>
#include "midi_message.h"
#include "transport_in.h"

/* Device independent MIDI driver. */

typedef struct Midi_in Midi_in;

struct Midi_in {
    Transport_in *transport;
    Midi_message *message;
    uint8_t buffer[3];
    uint8_t running_status;
    uint8_t index;
    uint8_t index_max;
};

void midi_in_init(Midi_in *self, Transport_in *transport);

/* Wait for a MIDI message.
self: The midi node to get the message on.
message: The Midi_message structure to fill.
*/
void midi_in_wait(Midi_in *self, Midi_message *message);

typedef struct Midi_out Midi_out;

typedef void (Midi_out_put)(Midi_out *self, Midi_message *message);

struct Midi_out {
    Midi_out_put *put;
};

void midi_out_put(Midi_out *self, Midi_message *message);

#endif
