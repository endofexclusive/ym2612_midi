TARGET = test.out
OBJECTS = test.o ym_midi.o ym.o midi_message.o
UNITDIR = ../..
CFLAGS = -I $(UNITDIR) -std=c99 -Wall
VPATH = $(UNITDIR)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

