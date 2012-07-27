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

