#ifndef TRANSPORT_IN_H
#define TRANSPORT_IN_H

typedef struct Transport_in Transport_in;
typedef uint8_t (*Transport_in_get)(Transport_in *self);

struct Transport_in {
    Transport_in_get get;
};

#endif

