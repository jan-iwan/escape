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

int vfcursor(FILE* file, enum Cursor code, va_list arg) {
    if(code > left)
        return -1;

    int printed;

    // only escape sequences up, down, right and left
    // use an argument
    if(code < up)
        printed = fprintf(file, "\x1b[%s", cursor_seq[code]);

    else
        printed = fprintf(file, "\x1b[%d%s", va_arg(arg, int), cursor_seq[code]);

    return printed;
}
