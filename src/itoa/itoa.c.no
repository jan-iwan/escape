#include "itoa.h"

#define BASE 10

unsigned short base10_itoa(unsigned short x, char* outbuf) {
    static char inbuf[6];
    register char* inbufptr = &inbuf[0];
    register unsigned short i = 0;

    // convert to decimal (reversed)
    do {
        register unsigned short rem  = x % BASE;
        inbuf[i++] = rem + '0';
        x = x/BASE;
    } while(x != 0);

    // reverse string
    unsigned short ibak = i;
    while(i--)
        outbuf[i] = *inbufptr++;

    return ibak;
}
