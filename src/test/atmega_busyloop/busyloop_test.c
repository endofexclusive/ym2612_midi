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

#include "busyloop.h"

#define M 1000

#define TEST_MS 1
#define TEST_US 0
#define TEST TEST_MS

int main(void)
{
    DDRA |= _BV(DDA0);

    while(1) {
        PORTA ^= _BV(PORTA0);
        busyloop_delay_ms(M);
    }
    return 0;
}
