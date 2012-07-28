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

/* Declare static? */
void delay_us_impl(uint16_t t)
{
    dprint("Delaying %d us.\n", t);
}

void set_data_impl(uint8_t data)
{
    dprint("DATA: $%x.\n", data);
}

void set_control_impl(struct ym_control c)
{
    /* Assume that signal NRD is always high. Assume that
    signal NWR is always low. */
    /* Start with ALL signals low. */
    /* Set NRD. */
    if (c.A0)
    {
        /* Set A0. */
    }
    if (c.A1)
    {
        /* Set A1. */
    }
    if (c.NCS)
    {
        /* Set NCS. */
    }
    if (c.NIC)
    {
        /* Set NIC. */
    }
    /* Displaying the implementation behavior. */
    dprint("[NIC:%x ", c.NIC);
    dprint("NCS:%x ", c.NCS);
    dprint("NRD:%x ", 0 !=  (c.NRD));
    dprint("NWR:%x ", 0 !=  (c.NWR));
    dprint("NRD:%x ", 0);
    dprint("NWR:%x ", 1);
    dprint("A1:%x ", c.A1);
    dprint("A0:%x]\n", c.A0);
}

int main(void)
{
    Ym_driver yd;
    ym_init(&yd, set_control_impl, set_data_impl, delay_us_impl);
    ym_set(&yd, ym_PORT1, 0xaa, 0xbb);
    return 0;
}

