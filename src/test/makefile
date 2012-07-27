midi: midi_test hex2bin
	./hex2bin | ./midi_test
hex2bin: hex2bin.c
	cc hex2bin.c -o hex2bin
midi_test: midi_test.c ../midi.c hex2bin ../*.h
	cc midi_test.c ../midi.c -I ../ -o midi_test

midi_clean: midi_test.c ../midi.c hex2bin ../*.h
	rm -f hex2bin midi_test

