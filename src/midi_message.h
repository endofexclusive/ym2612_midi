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
