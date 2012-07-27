#include "transport_in.h"

typedef struct Console_in Console_in;

struct Console_in {
    Transport_in parent;
};

void console_in_init(Console_in *self);

