#include "variable_color.h"

#include "escape.h"
#include "buffer.h"
#include "itoa/itoa.h"

extern char* buf;
extern unsigned bufptr;

int variable_color(enum ColorEsc code) {
    if(code > MAX_ESC)
        return 1;

    bufptr += base10_itoa(code, &buf[bufptr]);
    return 0;
}
