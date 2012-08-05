TARGET = unix_ym
CFILES = test.c ym.c
UNITDIR = ../..
CFLAGS = -I $(UNITDIR) -std=c99 -g -Wall -DDEBUG
VPATH = $(UNITDIR)

OBJECTS = $(CFILES:.c=.o)

test: $(TARGET)
	./$(TARGET)
	
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)

# Every non-.PHONY rule must update a file with the exact
# name of its target.  Make sure every command script touches
# the file "$@"-- not "../$@", or "$(notdir $@)", but exactly
# $@. That way you and GNU make always agree.
# http://mad-scientist.net/make/rules.html

