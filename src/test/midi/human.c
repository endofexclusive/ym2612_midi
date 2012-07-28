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

/* This program pretty-prints MIDI messages. The source code
is not very pretty though. */

#include <assert.h>
//#include <stdio.h>
#include "debug.h"
#include "transport_in.h"
#include "raw_in.h"
#include "pretty_out.h"

int main(void)
{
    Transport_in *tin;
    Raw_in rin;
    Midi_in min;
    Midi_message msg;

    Midi_out *mout;
    Pretty_out pout;

    raw_in_init(&rin);
    tin = (Transport_in *) &rin;

    pretty_out_init(&pout);
    mout = (Midi_out *) &pout;

    midi_in_init(&min, tin);
    while(1) {
        midi_in_wait(&min, &msg);
        mout->put(mout, &msg);
//        midi_out_put(mout, &msg);
    }
}

