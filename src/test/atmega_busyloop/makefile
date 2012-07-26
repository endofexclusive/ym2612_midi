TARGET = busyloop_test
OBJECTS = busyloop_test.o busyloop.o
SRCDIR = ../src
DEPS = $(SRCDIR)/*.h
INC = -I$(SRCDIR)
VPATH = $(SRCDIR)
CC = avr-gcc
MCU=atmega16
OPTLEVEL=0

CFLAGS = -mmcu=$(MCU) -std=c99 -g \
         -O$(OPTLEVEL) \
         -Wall -Wextra -Wstrict-prototypes \
         -pedantic $(INC)

all: $(TARGET)

$(TARGET): $(OBJECTS)

$(OBJECTS): $(DEPS)

program: $(TARGET)
	sudo avarice -g --erase --program --file $(TARGET)

gdbserver: $(TARGET)
	sudo avarice -g --erase --program --file $(TARGET) localhost:1212

gdb: $(TARGET)
	avr-gdb -x gdbinit

clean:
	rm -f $(OBJECTS) $(TARGET)

