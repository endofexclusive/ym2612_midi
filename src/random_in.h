#ifndef RANDOM_IN_H
#define RANDOM_IN_H

typedef struct Random_in Random_in;

struct Random_in {
    Transport_in parent;
    uint8_t seed;
};

void random_in_init(Random_in *self, uint8_t seed);

#endif

