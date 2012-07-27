TARGET = transport_in_test.out
OBJECTS = random_in.o uart_in.o test.o
UNITDIR = ../..
CFLAGS = -I $(UNITDIR) -std=c99 -Wall
VPATH = $(UNITDIR)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)

