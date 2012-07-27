/* Programmet hex2bin läser in tecken från stdin, tolkar som
hexadecimala tal och skriver till stdout. Programmet avslutas
med EOF. Tecken som inte är 0-9, a-f eller A-F ignoreras. */

#include <stdio.h>
#include <ctype.h>

/* int hexchartoint(char) tar ett tecken, tolkar det som ett
hexadecimalt tal och returnerar talet. Om tecknet inte motsvarar
ett hexadecimalt tal så returneras -1. */

static int hexchar_to_int(char c)
{
    const char *hexchar = "abcdef0123456789ABCDEF";
    int i;

    i = 0;
    while (i < (16 + 6)) {
        if (c == *(hexchar + i)) {
            return (i + 10) % 16;
        }
        i++;
    }
    return -1;
}

int main(void)
{
    int n;
    int c;
    int state;
    int acc;

    c = getchar();
    state = 0;
    while (c != EOF) {
        n = hexchar_to_int(c);
        if (-1 != n) {
            if (!state) {
                acc = n * 16;
                state = 1;
            } else {
                acc += n;
                putchar(acc);
                state = 0;
            }
        } else {
            state = 0;
        }
        c = getchar();
    }
    return 0;
}

