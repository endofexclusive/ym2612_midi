UNITDIR = ../..
CFLAGS = -I $(UNITDIR) -std=c99 -Wall
VPATH = $(UNITDIR)

target: midi_test hex2bin human

pretty_out.o: pretty_out.c

test: midi_test hex2bin
	./hex2bin < testdata_in | ./midi_test > testdata_out
	diff testdata_out testdata_oracle

human: human.c midi.c raw_in.c pretty_out.c

human_test: human hex2bin
	./hex2bin < testdata_in | ./human

hex2bin: hex2bin.c

midi_test: midi_test.c midi.c raw_in.c

clean:
	rm -f hex2bin midi_test testdata_out human *.o

