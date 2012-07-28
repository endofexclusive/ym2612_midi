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

/* The purpose of this test is to compare the output of the
parser with an oracle. */

#include <assert.h>
#include <stdio.h>
#include "debug.h"
#include "transport_in.h"
#include "raw_in.h"
#include "midi.h"

void midi_message_print(Midi_message *m)
{
    switch (m->status & 0xf0) {
        case 0x80:
        case 0x90:
        case 0xa0:
        case 0xb0:
        case 0xe0:
            printf("0x%x 0x%x 0x%x\n", m->status, m->data1,
              m->data2);
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
    Raw_in cin;
    Transport_in *tin;

    raw_in_init(&cin);
    tin = (Transport_in *) &cin;
    
    midi_in_init(&min, tin);
    while(1) {
        midi_in_wait(&min, &msg);
        midi_message_print(&msg);
    }
}

