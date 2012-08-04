TARGET = ym_synth.out
CFILES = main.c ym.c busyloop.c ym_midi.c midi_message.c
OPTLEVEL=s
CFLAGS = -mmcu=$(MCU) -std=c99 -g -O$(OPTLEVEL) -Wall
LDFLAGS = -mmcu=$(MCU) -Wl,-Map,$(TARGET).map
VPATH = ..
MCU = atmega16
CC = avr-gcc

OBJECTS = $(CFILES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJECTS): $(DEPS)

size: $(TARGET)
	avr-size $(TARGET)

program: $(TARGET)
	sudo avarice -g --erase --program --file $(TARGET)

gdbserver: $(TARGET)
	sudo avarice -g --erase --program --file $(TARGET) localhost:1212

gdb: $(TARGET)
	avr-gdb -x gdbinit

clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).map

# Every non-.PHONY rule must update a file with the exact
# name of its target.  Make sure every command script touches
# the file "$@"-- not "../$@", or "$(notdir $@)", but exactly
# $@. That way you and GNU make always agree.
# http://mad-scientist.net/make/rules.html

