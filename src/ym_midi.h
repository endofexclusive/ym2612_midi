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

#ifndef YM_MIDI_H
#define YM_MIDI_H

/** @file
MIDI layer for YM2612.

@author Martin Åberg martin@fripost.org
*/

#include "midi.h"
#include "ym.h"

typedef struct Ym_midi Ym_midi;

struct Ym_midi {
    Midi_out parent;
    Ym_driver *driver;
};

void ym_midi_init(Ym_midi *self, Ym_driver *driver);

#endif
