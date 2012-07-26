#include "busyloop.h"

#define M 1000

#define TEST_MS 1
#define TEST_US 0
#define TEST TEST_MS

int main(void)
{
    DDRA |= _BV(DDA0);

    while(1) {
        PORTA ^= _BV(PORTA0);
        busyloop_delay_ms(M);
    }
    return 0;
}
