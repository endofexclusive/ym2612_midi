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

