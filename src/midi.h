#ifndef MIDI_H
#define MIDI_H

#include <stdbool.h>
#include "transport_in.h"

typedef struct Midi_message Midi_message;
typedef struct Midi_in Midi_in;
typedef struct Midi_out Midi_out;

struct Midi_message {
    uint8_t status;
    uint8_t data[2];
    uint8_t data1, data2;
};

struct Midi_in {
    Transport_in transport;
    /* This is for channel messages only. */
    Midi_message *message;
    uint8_t running_status;
    uint8_t index;
};

struct Midi_out {
    Transport_out transport;
};

bool midi_message_is_noteon(Midi_message *m);
bool midi_message_is_noteoff(Midi_message *m);
bool midi_message_is_control(Midi_message *m);
bool midi_message_type(Midi_message *m);

void midi_in_init(Midi_in *self, Transport_in *transport);
void midi_in_get(Midi_in *self, Midi_message *message);

void midi_out_init(Midi_out *self, Transport_out *transport);
void midi_out_put(Midi_out *self, Midi_message *message);

#endif

