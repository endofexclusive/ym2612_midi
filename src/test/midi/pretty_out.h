#include <midi.h>
typedef struct Pretty_out Pretty_out;

struct Pretty_out {
    Midi_out parent;
    unsigned int count;
};

void pretty_out_init(Pretty_out *self);

