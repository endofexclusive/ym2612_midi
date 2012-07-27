#include <stdio.h>

/* NDEBUG is for assertions, DEBUG for debug printout. */
#define DEBUG_LEVEL 1
#define DEBUG_LEVEL_PRINT 1

#define dprint(fmt, ...) \
    do { \
        if (DEBUG_LEVEL >= DEBUG_LEVEL_PRINT) { \
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__); \
            fflush(stderr); \
        } \
    } while (0)

#define dputs(string) dprint("%s\n", string)
#if DEBUG_LEVEL >= 1
#define D if(1)
#else
#define D if(0)
#endif
