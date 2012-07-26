#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "ym.h"

static uint8_t ym_calculate_address(uint8_t channel,
  uint8_t operator);

/* These constants are part of the public interface. */
const uint8_t ym_PORT0 = 0x00;
const uint8_t ym_PORT1 = 0x01;

/* Because the structures are declared in static storage
(static or at file scope), they are initialized with all numeric
members zero and all pointers null. In dynamic storage, use
struct ym_control c  = {0}. */
static const struct ym_control CONTROL_RESET = {.A0 = 0, .A1 = 0,
  .NWR = 1, .NRD = 1, .NCS = 1, .NIC = 0};
static const struct ym_control CONTROL_IDLE = {.A0 = 0, .A1 = 0,
  .NWR = 1, .NRD = 1, .NCS = 1, .NIC = 1};
static const struct ym_control CONTROL_WRITE = {.A0 = 0, .A1 = 0,
  .NWR = 0, .NRD = 1, .NCS = 0, .NIC = 1};
static const uint8_t ym_A0_ADDRESS = 0x00;
static const uint8_t ym_A0_DATA = 0x01;

/* Hold state for the ym driver module. */
static struct ym_config *config;

static uint8_t shadow_0x30[0x10];

void ym_init(struct ym_config *c)
{
    /* Make sure that not both MCU and chip activates their
    output. */
    config = c;
}

void ym_reset(void)
{
    config->set_control(CONTROL_RESET);
    /* Sleep for 192 cycles, equals 24 us @ 8MHz. This is the
    reset pulse width. */
    config->delay_us(24);
    config->set_control(CONTROL_IDLE);
    int i = sizeof(shadow_0x30) / sizeof(uint8_t);
    while(i)
    {
        shadow_0x30[i--] = 0;
    }
}
/* FIXME: The parameter types... */
static void ym_write_lowlevel(uint8_t a0, uint8_t a1, uint8_t d)
{
    /* FIXME: The variable name this_control sucks. */
    struct ym_control this_control = CONTROL_WRITE;
    this_control.A0 = a0;
    this_control.A1 = a1;
    config->set_data(d);
    config->set_control(this_control);
    config->delay_us(1);
    this_control.NCS = 1;
    config->set_control(this_control);
}

/* According to translated documentation, wait 17 cycles (2 us)
after write of address and wait 83 cycles (10 us) after write
of data (8MHz). */

void ym_set(uint8_t port, uint8_t reg, uint8_t value)
{
    /* Assert the user input (but not internal stuff). */
    assert(ym_PORT0 == port || ym_PORT1 == port);
    /* Assert reg. */

    /* Select register. */
    ym_write_lowlevel(ym_A0_ADDRESS, port, reg);
    /* Wait for write to settle. */
    config->delay_us(2);

    /* Write data to current register. */
    ym_write_lowlevel(ym_A0_DATA, port, value);
    /* Wait for write to settle. */
    config->delay_us(10);
}

void ym_key_on(uint8_t channel)
{
    assert(channel <= 5);
    ym_set(ym_PORT0, 0x28, 0xf0 + channel);
}

void ym_key_off(uint8_t channel)
{
    assert(channel <= 5);
    ym_set(ym_PORT0, 0x28, 0x00 + channel);
}

void ym_set_multiplier(uint8_t channel, uint8_t operator,
  uint8_t multiplier)
{
    uint8_t port, *valuep, address;

    assert(channel <= 5);
    assert(operator <= 3);
    assert(multiplier <= 0x0f);

    port = channel / 3;
    address = ym_calculate_address(channel, operator);
    valuep = shadow_0x30 + address;
    *valuep = (*valuep & 0xf0) + multiplier;
    ym_set(port, 0x30 + address, *valuep) ;
}

void ym_set_detune(uint8_t channel, uint8_t operator,
  uint8_t detune)
{
    uint8_t port, *valuep, address;

    assert(channel <= 5);
    assert(operator <= 3);
    assert(detune <= 0x07);

    port = channel / 3;
    address = ym_calculate_address(channel, operator);
    valuep = shadow_0x30 + address;
    *valuep = (*valuep & 0x8f) + (detune << 4);
    ym_set(port, 0x30 + address, *valuep) ;
}

void ym_set_amplitude(uint8_t channel, uint8_t operator,
  uint8_t amplitude)
{
    uint8_t port, address;

    assert(channel <= 5);
    assert(operator <= 3);
    assert(amplitude <= 0x7f);

    port = channel / 3;
    address = ym_calculate_address(channel, operator);
    ym_set(port, 0x40 + address, amplitude);
}

static uint8_t ym_calculate_address(uint8_t channel,
  uint8_t operator)
{
    return operator * 4 + channel % 3;
}

/* Remove asserts by defining NDEBUG. */

