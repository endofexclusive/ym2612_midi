#include <assert.h>
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
    assert(EOF != c);
    return c;
}

void console_in_init(Console_in *self)
{
    Transport_in *t_in = &(self->parent);
    t_in->get = (Transport_in_get) console_in_get;
    dputs("Initializing console");
}

int main(void)
{
    Midi_in min;
    Console_in cin;

    console_in_init(&cin);
    midi_in_init(&min, &cin);
}

