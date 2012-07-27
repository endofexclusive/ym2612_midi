#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>

/* NDEBUG is for assertions, DEBUG for debug printout. */
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

