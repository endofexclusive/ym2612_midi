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
#include "ym.h"

/* Declare static? */
void delay_us_impl(uint16_t t)
{
    printf("Delaying %d us.\n", t);
}

void set_data_impl(uint8_t data)
{
    printf("DATA: $%x.\n", data);
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
    printf("[NIC:%x ", c.NIC);
    printf("NCS:%x ", c.NCS);
/*
    printf("NRD:%x ", 0 !=  (c&ym_NRD));
    printf("NWR:%x ", 0 !=  (c&ym_NWR));
*/
    printf("NRD:%x ", 0);
    printf("NWR:%x ", 1);
    printf("A1:%x ", c.A1);
    printf("A0:%x]\n", c.A0);
}

/* C99 allows initialization of struct members by name. */
struct ym_config c = {.set_control = set_control_impl,
  .set_data = set_data_impl, .delay_us = delay_us_impl};

int main(void)
{
    ym_init(&c);
    ym_set(ym_PORT1, 0xaa, 0xbb);
    return 0;
}

