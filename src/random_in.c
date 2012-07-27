#include <inttypes.h>
#include "transport_in.h"
#include "random_in.h"

static uint8_t random_in_get(Random_in *self)
{
    /* Calculate something random. */
    self->seed += 27;
    return self->seed;
}

void random_in_init(Random_in *self, uint8_t seed)
{
    ((Transport_in *) self)->get =
      (Transport_in_get *) random_in_get;
    self->seed = seed;
}

