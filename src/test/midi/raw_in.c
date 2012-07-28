/* Copyright (C) 2012 Martin Åberg

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program (COPYING).  If not, see <http://www.gnu.org/licenses/>. */

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
