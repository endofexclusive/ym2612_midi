UNITDIR = ../..
CFLAGS = -I $(UNITDIR) -std=c99 -Wall
VPATH = $(UNITDIR)

test: midi_test hex2bin
	./hex2bin < testdata_in | ./midi_test > testdata_out
	diff testdata_out testdata_oracle

hex2bin: hex2bin.c

midi_test: midi_test.c midi.c

clean:
	rm -f hex2bin midi_test testdata_out

