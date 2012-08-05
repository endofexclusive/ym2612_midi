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
    Ym_driver yd, *ydp;

    ydp = &yd;
    ym_init(ydp, set_control_impl, set_data_impl,
      delay_us_impl);
    ym_reset(ydp);

    for (int ch = 0; ch < 6; ch++) {
        for (int op = 0; op < 4; op++) {
            ym_set_key_scale(ydp, ch, op, 1);
            ym_set_key_scale(ydp, ch, op, 3);
            ym_set_attack_rate(ydp, ch, op, 31);
        }
    }

    return 0;
}

