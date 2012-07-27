#ifndef MIDI_H
#define MIDI_H

/** @file
Device independent MIDI driver.
@author Martin Åberg martin@fripost.org
*/

#include <stdbool.h>
#include "midi_message.h"
#include "transport_in.h"

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

/** Wait for a MIDI message.
@param self The midi node to get the message on.
@param message The Midi_message structure to fill. */
void midi_in_wait(Midi_in *self, Midi_message *message);

typedef struct Midi_out Midi_out;

typedef void (Midi_out_put)(Midi_out *self, Midi_message *message);

struct Midi_out {
    Midi_out_put *put;
};

void midi_out_put(Midi_out *self, Midi_message *message);

#endif
