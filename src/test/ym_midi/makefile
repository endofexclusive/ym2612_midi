TARGET = test.out
OBJECTS = test.o ym_midi.o ym.o midi_message.o
UNITDIR = ../..
CFLAGS = -I $(UNITDIR) -std=c99 -Wall -DDEBUG
VPATH = $(UNITDIR)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)

