#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "raw_in.h"

static uint8_t raw_in_get(Raw_in *self)
{
    int c;

    c = getchar();
    if (EOF == c) {
        exit(0);
    }
    return c;
}

void raw_in_init(Raw_in *self)
{
    Transport_in *t_in = &(self->parent);
    t_in->get = (Transport_in_get *) raw_in_get;
    dputs("Initializing raw in");
}
