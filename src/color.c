#include "color.h"

#include <stdbool.h>
#include "escape.h"
#include "buffer.h"

extern char* buf;
extern unsigned bufptr;

const char* color(const char* fmt) {
    unsigned bak = bufptr - sizeof(ESC);

    bool background = false;
    bool bright = false;

    // normal foreground by default
    append_char(buf, bufptr, '3');

    char ch;
    if((ch = *fmt++) == 'B') {
            background = true;

            // replace '3' with '4'
            bp--;
            append_char(buf, bufptr, '4');

            ch = *fmt++;
    }
    if(ch == 'h') {
            bright = true;

            bp--;
            if(background) {
                // replace '4' with "10"
                append_char(buf, bufptr, '1');
                append_char(buf, bufptr, '0');
            }
            else {
                // replace '3' with '9'
                append_char(buf, bufptr, '9');
            }

            ch = *fmt++;
    }

    // color
    if(ch >= '0' && ch <= '7') {
        append_char(buf, bufptr, ch);
    }

    // invalid
    else {
        bp = bak;
        append_char(buf, bufptr, FMT);
        append_char(buf, bufptr, 'c');

        if(background)
            append_char(buf, bufptr, 'B');
        if(bright)
            append_char(buf, bufptr, 'h');

        append_char(buf, bufptr, ch);
    }

    return fmt;
}
