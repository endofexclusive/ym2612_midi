#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug.h"
#include "transport_in.h"
#include "midi.h"

typedef struct Console_in Console_in;

struct Console_in {
    Transport_in parent;
};

void console_in_init(Console_in *self);

static uint8_t console_in_get(Console_in *self)
{
    int c;

    c = getchar();
    if (EOF == c) {
        exit(0);
    }
    return c;
}

void console_in_init(Console_in *self)
{
    Transport_in *t_in = &(self->parent);
    t_in->get = (Transport_in_get) console_in_get;
    dputs("Initializing console");
}

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

