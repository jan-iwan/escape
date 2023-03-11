#include "itoa.h"

#define BASE 10

// very basic and static itoa
ushort itoa(ushort x, char* outbuf) {
    static char inbuf[6];
    register char* inbufptr = &inbuf[0];
    register ushort i = 0;

    // convert to decimal (reversed)
    do {
        register ushort rem  = x % BASE;
        inbuf[i++] = rem + '0';
        x = x/BASE;
    } while(x != 0);

    // reverse string
    // outbuf[i] = '\0';
    ushort ibak = i;
    while(i--)
        outbuf[i] = *inbufptr++;

    return ibak;
}
