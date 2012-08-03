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

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

/* Generate debug output. Note that NDEBUG is for assertions
(see assert.h), DEBUG for debug printout. */

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define dprint(fmt, ...) \
    do { \
        if (DEBUG_TEST) { \
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__); \
            fflush(stderr); \
        } \
    } while (0)

#define dputs(string) dprint("%s\n", string)

#endif /* DEBUG_H */
