/** @file
Driver for the YM2612 chip. Here we describe the driver
more.

@author Martin Åberg martin@fripost.org

@todo Add const qualifiers to function parameters where
suitable.

@todo Define types. That will prevent bugs that appear because
functions are called with parameters in wrong order.

*/

#if __STDC_VERSION__ < 199901L
# error "C99 is required."
#endif

#include <inttypes.h>

/** Chip input pins. @sa ym_config.set_control()
*/
struct ym_control
{
    /** Select address or data mode. */
    unsigned int A0 : 1;
    /** Port selection. */
    unsigned int A1 : 1;
    /** Write mode on data bus. */
    unsigned int NWR : 1;
    /** Read mode on data bus. */
    unsigned int NRD : 1;
    /** Chip select. */
    unsigned int NCS : 1;
    /** Initialize registers. */
    unsigned int NIC : 1;
};

/** Hardware access functions. */
struct ym_config
{
    /** Set the control signals on the YM chip. @param value
    Filled in by the driver before call. */
    void (*set_control)(struct ym_control control);

    /** Write to the 8-bit bidrectional data bus. @param data
    The data to write. */
    void (*set_data)(uint8_t data);

    /** Delay the execution for a given number of
    microseconds. @param time The number of microseconds to
    delay. */
    void (*delay_us)(uint16_t time);
};

/** Identifies port 0. @sa ym_set() @todo Represent this value
as an enum? */
extern const uint8_t ym_PORT0;
/** Identifies port 1. @sa ym_set() */
extern const uint8_t ym_PORT1;

/** Write a value to a chip register. @param port This must
be ym_PORT0 or ym_PORT1. @param reg The YM register to write
to. @param value The value that will be written. */
void ym_set(uint8_t port, uint8_t reg, uint8_t value);

/** Initialize the driver. After the driver has been
initialized, ym_reset() should be called by the user to perform
a chip reset. @param fs Functions for performing hardware
access. These are supplied by the user. */
void ym_init(struct ym_config *fs);

/** Perform chip hardware reset. @pre The driver has been
initialized by ym_init(). @post All chip registers and shadow
registers are set to zero. */
void ym_reset(void);

/** Play a note on @e channel. */
void ym_key_off(uint8_t channel);

/** Stop playing the note on @e channel. */
void ym_key_on(uint8_t channel);

/** Set the frequency @e multiplier of a @e channel @e
operator. */
void ym_set_multiplier(uint8_t channel, uint8_t operator,
  uint8_t multiplier);

/** Set the frequency @e detune factor for a @e channel
@e operator. @todo This function has to be tested. */
void ym_set_detune(uint8_t channel, uint8_t operator,
  uint8_t detune);

/** Set the @e amplitude of an @e operator. */
void ym_set_amplitude(uint8_t channel, uint8_t operator,
  uint8_t amplitude);

