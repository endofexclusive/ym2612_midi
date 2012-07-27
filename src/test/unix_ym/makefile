PROGS = test
OBJECTS = ym.o test.o
SRCDIR = ../..
VPATH = $(SRCDIR)

CFLAGS = -I $(SRCDIR) -std=c99 -Wall -Wextra -pedantic \
         -Wstrict-prototypes

all: $(PROGS)

$(PROGS): $(OBJECTS)

$(OBJECTS): $(DEPS)

clean:
	rm -f ym.o test.o test

# Every non-.PHONY rule must update a file with the exact
# name of its target.  Make sure every command script touches
# the file "$@"-- not "../$@", or "$(notdir $@)", but exactly
# $@. That way you and GNU make always agree.

# http://mad-scientist.net/make/rules.html

