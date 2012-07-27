#include <assert.h>
#include <stdio.h>
#include "debug.h"
#include "transport_in.h"
#include "console_in.h"
#include "midi.h"

void midi_message_pretty_print(Midi_message *m)
{
    if (midi_message_is_note_on(m)) {
        printf("Note-On, channel %x, key %x, vel %x\n", m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_note_off(m)) {
        printf("Note-Off, channel %x, key %x, vel %x\n", m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_control(m)) {
        printf("Control change, channel %x, #%x, value %x\n", m->status & 0x0f, m->data1, m->data2);
    } else if (midi_message_is_mode(m)) {
        printf("Channel mode, channel %x, #%x, value %x\n", m->status & 0x0f, m->data1, m->data2);
    }
}

int main(void)
{
    Midi_in min;
    Midi_message msg;
    Console_in cin;
    Transport_in *tin;

    console_in_init(&cin);
    tin = (Transport_in *) &cin;
    
    midi_in_init(&min, tin);
    while(1) {
        midi_in_wait(&min, &msg);
        midi_message_pretty_print(&msg);
    }
}

