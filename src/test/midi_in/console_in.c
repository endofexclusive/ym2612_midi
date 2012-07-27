#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "console_in.h"

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
    t_in->get = (Transport_in_get *) console_in_get;
    dputs("Initializing console");
}
