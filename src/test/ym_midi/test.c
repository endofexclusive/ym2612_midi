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

#include "debug.h"
#include "ym.h"
#include "ym_midi.h"

static void delay_us_impl(uint16_t t)
{
//    dprint("Delaying %d us.\n", t);
}

static void set_data_impl(uint8_t data)
{
//    dprint("DATA: $%x.\n", data);
}

static void set_control_impl(struct ym_control c)
{
//    dprint("[NIC:%x NCS:%x NRD:%x NWR:%x A1:%x A0:%x]\n", c.NIC,
//      c.NCS, c.NRD, c.NWR, c.A1, c.A0);
}

int main(void)
{
    Ym_driver yd;
    Ym_midi ym;
    Midi_message msg;
    Midi_out *mo;

    mo = (Midi_out *) &ym;
    ym_init(&yd, set_control_impl, set_data_impl, delay_us_impl);
    ym_reset(&yd);

    ym_midi_init(&ym, &yd);

    msg.status = 0xd4;
    msg.data1 = 0x10;
    msg.data2 = 0x00;
    mo->put(mo, &msg);



    return 0;
}

