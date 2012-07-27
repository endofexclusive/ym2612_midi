#include "transport_in.h"

typedef struct Raw_in Raw_in;

struct Raw_in {
    Transport_in parent;
};

void raw_in_init(Raw_in *self);

