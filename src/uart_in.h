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

#ifndef UART_IN_H
#define UART_IN_H

typedef struct Uart_in Uart_in;

struct Uart_in {
    Transport_in parent;
};

/* fixme: parameters. */
void uart_in_init(Uart_in *self, uint32_t baudrate,
  uint8_t bits, uint8_t stopbits, uint8_t parity);

#endif
