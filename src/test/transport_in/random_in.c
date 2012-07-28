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

#include <inttypes.h>
#include "transport_in.h"
#include "random_in.h"

static uint8_t random_in_get(Random_in *self)
{
    /* Calculate something random. */
    self->seed += 27;
    return self->seed;
}

void random_in_init(Random_in *self, uint8_t seed)
{
    ((Transport_in *) self)->get =
      (Transport_in_get *) random_in_get;
    self->seed = seed;
}

