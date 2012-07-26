/* Design issues: Shall the in- and out modules be
separated? What is common for them? Probably parsing midi
data. Shall the driver handle several midi ports? YES! Each
have some state structure then.

Make the code ROM-able! It can then also be shared. Don't
use .data and .bss sections. Don't use non-constant global
data. Data qualified by "static const" can be put in the .text
segment by the compiler. What about just "const" on global
data? */

#include <inttypes.h>
#include <debug.h>
#include <transport_in.h>
#include <random_in.h>
#include <uart_in.h>

int main(void)
{
    Transport_in *tin;
    Random_in rin;
    Serial_in sin;

    serial_in_init(&sin, 0,0,0,0);
    random_in_init(&rin, 13);
    tin = (Transport_in *) &sin;
    printf("Transporting %x\n", tin->get(tin));
    printf("Transporting %x\n", tin->get(tin));
    tin = (Transport_in *) &rin;
    printf("Transporting %x\n", tin->get(tin));
    printf("Transporting %x\n", tin->get(tin));
    return 0;
}
