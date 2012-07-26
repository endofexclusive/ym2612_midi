#ifndef UART_IN_H
#define UART_IN_H

typedef struct Uart_in Uart_in;

struct Uart_in {
    Transport_in parent;
};

/** @fixme Parameters. */
void uart_in_init(Uart_in *self, uint32_t baudrate,
  uint8_t bits, uint8_t stopbits, uint8_t parity);

#endif

