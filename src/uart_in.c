#include <inttypes.h>
#include "transport_in.h"
#include "uart_in.h"
#include "debug.h"

void uart_in_init(Uart_in *self, uint32_t baudrate,
  uint8_t bits, uint8_t stopbits, uint8_t parity)
{
    Transport_in *t_in = &(self->parent);

    t_in->get = (Transport_in_get) uart_in_get;
    /* Set up the hardware. */
}

