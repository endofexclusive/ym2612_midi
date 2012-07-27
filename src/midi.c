#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "debug.h"
#include "midi.h"

static bool is_status(uint8_t target)
{
    return (0x80 & target) ? true : false;
}

static bool is_data_byte(uint8_t target)
{
    return !is_status(target);
}

/*
static bool is_system_message(uint8_t status)
{
    return (0xf0 & status) ? true : false;
}
*/

static bool is_system_exclusive_message(uint8_t status)
{
    return (status == 0xf0) ? true : false;
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
    return ((0x80 <= status) && (status <= 0xef)) ? true : false;
}

/* This works for channel messages. */
static uint8_t number_of_data_bytes(uint8_t token)
{
    switch (token & 0xf0) {
        case 0x80:
        case 0x90:
        case 0xa0:
        case 0xb0:
        case 0xe0:
            return 2;
    }
    return 1;
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
        dprint("Real-time message 0x%x\n", token);
        /* self->message->status = token; */
        return false;
    }
    if (is_channel_message(token)) {
        self->running_status = token;
        /* Start building a new channel message. */
        self->buffer[0] = token;
        self->index = 0;
        self->index_max = number_of_data_bytes(token);
        dprint("Channel message 0x%x (%d data bytes).\n",
          token, self->index_max);
        return false;
    }
    if (is_system_common_message(token) ||
      is_system_exclusive_message(token)) {
        self->running_status = 0;
        self->buffer[0] = token;
        self->index = 0;
        self->index_max = number_of_data_bytes(token);
        dprint("System message 0x%x (%d data bytes).\n",
          token, self->index_max);
        return false;
        /*
        return try_emit(self);
        */
    }
    if (is_data_byte(token)) {
        if (is_channel_message(self->running_status)) {
            /* Continue building up the channel message. */
            self->buffer[++self->index] = token;
            dprint("buffer[%d] <- 0x%x\n", self->index, token);
            assert(0 != self->index);
            if (self->index == self->index_max) {
                /* We are done with this message. */
                self->message->status = self->running_status;
                self->message->data1 = self->buffer[1];
                self->message->data2 = self->buffer[2];
                self->index = 0;
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

void midi_in_wait(Midi_in *self, Midi_message *message)
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
    dprint("Emit [0x%x, 0x%x, 0x%x]\n", message->status,
      message->data1, message->data2);
}

void midi_in_init(Midi_in *self, Transport_in *transport)
{
    self->transport = transport;
    self->message = 0;
    self->running_status = 0;
    self->index = 0;
}

