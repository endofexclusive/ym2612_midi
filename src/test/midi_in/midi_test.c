#include <assert.h>
#include <stdio.h>
#include "debug.h"
#include "transport_in.h"
#include "console_in.h"
#include "midi.h"

void midi_message_print(Midi_message *m)
{
    switch (m->status & 0xf0) {
        case 0x80:
        case 0x90:
        case 0xa0:
        case 0xb0:
        case 0xe0:
            printf("0x%x 0x%x 0x%x\n", m->status, m->data1, m->data2);
            break;
        case 0xc0:
        case 0xd0:
            printf("0x%x 0x%x\n", m->status, m->data1);
            break;
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
        midi_message_print(&msg);
    }
}

