#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "midi.h"

enum Midi_channel_voice_messages {
    STATUS_ANY = 0x80,
    STATUS_NOTE_OFF = 0x80,
    STATUS_NOTE_ON = 0x90,
    STATUS_POLYPHONIC_AFTERTOUCH = 0xa0,
    STATUS_CONTROL_CHANGE = 0xb0,
    STATUS_PROGRAM_CHANGE = 0xc0,
    STATUS_CHANNEL_AFTERTOUCH = 0xd0,
    STATUS_PITCH_BEND = 0xe0
};

enum Midi_channel_mode_messages {
    STATUS_MODE_CHANGE = 0xb0
};

enum Midi_system_exclusive_messages { 
    /* ID, ..., <any status byte> */
    STATUS_SYSTEM_EXCLUSIVE = 0xf0
};

enum Midi_system_common_messages {
    /* How long is this message? */
    STATUS_MIDI_TIME_CODE_QUARTER_FRAME = 0xf1,
    STATUS_SONG_POSITION_POINTER = 0xf2,
    STATUS_SONG_SELECT = 0xf3,
    STATUS_SYSTEM_COMMON_UNDEFINED1 = 0xf4,
    STATUS_SYSTEM_COMMON_UNDEFINED2 = 0xf5,
    STATUS_TUNE_REQUEST = 0xf6,
    STATUS_END_OF_EXCLUSIVE = 0xf7
};

enum Midi_system_real_time_messages {
    STATUS_TIMING_CLOCK = 0xf8,
    STATUS_SYSTEM_REAL_TIME_UNDEFINED1 = 0xf9,
    STATUS_START = 0xfa,
    STATUS_CONTINUE = 0xfb,
    STATUS_STOP = 0xfc,
    STATUS_SYSTEM_REAL_TIME_UNDEFINED2 = 0xfd,
    STATUS_ACTIVE_SENSING = 0xfe,
    STATUS_SYSTEM_RESET = 0xff
};

static bool is_status(uint8_t token) {
    return token & STATUS_ANY;
}

void midi_in_get(Midi_in *self, Midi_message *message)
{
    bool parse_done;

    parse_done = false;
    self->running_status = 0;
    message->status = 0x00;
    self->message = message;
    do {
        uint8_t token;
        token = self->transport.get(&self->transport);
        parse_done = parse(self, token);
    } while (false == parse_done);
}

