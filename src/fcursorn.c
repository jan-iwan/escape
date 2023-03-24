#include "escape.h"

#include <stdio.h>
#include <stdarg.h>

static const char* const cursor_seq[] = {
    [wrap_on]   = "?7h",
    [wrap_off]  = "?7l",
    [save]      = "s",
    [restore]   = "u",
    [up]        = "A",
    [down]      = "B",
    [right]     = "C",
    [left]      = "D",
};

int fcursorn(FILE* file, enum Cursor code, int nargs, ...) {
    va_list arg;
    va_start(arg, nargs);

    if(code > left)
        return -1;

    int printed;

    // only escape sequences up, down, right and left
    // use an argument
    if(code < up)
        printed = fprintf(file, "\x1b[%s", cursor_seq[code]);

    else {
        int d = nargs > 0 ? va_arg(arg, int) : 0;

        printed = fprintf(file, "\x1b[%d%s", d, cursor_seq[code]);
    }

    va_end(arg);
    return printed;
}
