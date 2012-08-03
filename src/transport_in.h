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

#ifndef TRANSPORT_IN_H
#define TRANSPORT_IN_H

#include <stdint.h>

/* Interface for for a MIDI input transporter. */

typedef struct Transport_in Transport_in;
typedef uint8_t (Transport_in_get)(Transport_in *self);

struct Transport_in {
    Transport_in_get *get;
};

#endif
