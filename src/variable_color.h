#include "escape.h"

#define BASE 10

inline unsigned short base10_itoa(unsigned short x, char* outbuf) {
    char inbuf[6];
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

inline int variable_color(char* buf, unsigned* bufptr, enum ColorEsc code) {
    if(code > MAX_ESC)
        return 1;

    *bufptr += base10_itoa(code, &buf[*bufptr]);
    return 0;
}
