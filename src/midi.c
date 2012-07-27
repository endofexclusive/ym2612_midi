#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "midi.h"

static bool is_status_message(uint8_t status)
{
    return (0x80 & status) ? true : false;
}

static bool is_data_byte(uint8_t status)
{
    return !is_status_message(status);
}

/*
static bool is_system_message(uint8_t status)
{
    return (0xf0 & status) ? true : false;
}
*/

static bool is_system_exclusive_message(uint8_t status)
{
    return ((0xf1 <= status) && (status <= 0xf7)) ? true : false;
}

static bool is_system_common_message(uint8_t status)
{
    return ((0xf1 <= status) && (status <= 0xf7)) ? true : false;
}

static bool is_system_real_time_message(uint8_t status)
{
    return (0xf8 <= status) ? true : false;
}

static bool is_channel_message(uint8_t status)
{
    return (0xf8 <= status) ? true : false;
}

/* Returns 0, 1 or 2. */
uint8_t number_of_data_bytes(uint8_t token)
{
    return token%2;
}

/*
static bool try_emit(Midi_in *self)
{
    if (self->index == number_of_data_bytes(self->buffer[0])) {
        self->message->status = self->buffer[0];
        self->message->data1 = self->buffer[1];
        self->message->data2 = self->buffer[2];
        self->buffer[0] = 0;
        return true;
    }
    return false;
}
*/

/* parse only emits channel messages. It aims to be robust
and comply with the "MIDI 1.0 Detailed Specification, document
version 4.2". */
static bool parse(Midi_in *self, uint8_t token)
{
    if (is_system_real_time_message(token)) {
        /* self->message->status = token; */
        return false;
    }
    if (is_channel_message(token)) {
        self->running_status = token;
        /* Start building a new channel message. */
        self->buffer[0] = token;
        self->index = 0;
        self->index_max = number_of_data_bytes(token);
        return false;
    }
    if (is_system_common_message(token) ||
      is_system_exclusive_message(token)) {
        self->running_status = 0;
        self->buffer[0] = token;
        return false;
        /*
        self->index = 0;
        self->index_max = number_of_data_bytes(token);
        return try_emit(self);
        */
    }
    if (is_data_byte(token)) {
        if (is_channel_message(self->running_status)) {
            self->buffer[0] = self->running_status;
            /* Continue building up the channel message. */
            self->buffer[++self->index] = token;
            assert(0 != self->index);
            if (self->index == self->index_max) {
                /* We are done with this message. */
                self->message->status = self->buffer[0];
                self->message->data1 = self->buffer[1];
                self->message->data2 = self->buffer[2];
                self->buffer[0] = 0;
                return true;
            }
            return false;
        }
        /*
        if (is_system_common_message(self->buffer[0])) {
            self->buffer[self->index++] = token;
            assert(0 != self->index);
            return try_emit(self);
        }
        */
        /* No known use for this data byte. */
        return false;
    }
    /* The token was not recognized at all. */
    return false;
}

void midi_in_get(Midi_in *self, Midi_message *message)
{
    bool parse_done;

    parse_done = false;
    message->status = 0x00;
    self->message = message;
    do {
        uint8_t token;
        token = self->transport->get(self->transport);
        parse_done = parse(self, token);
    } while (false == parse_done);
}

void midi_in_init(Midi_in *self, Transport_in *transport)
{
    self->transport = transport;
    self->message = 0;
    self->running_status = 0;
    self->index = 0;
}

