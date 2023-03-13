#include "escape.h"

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

int cursor(enum CursorEsc code, ...) {
    va_list arg;
    va_start(arg, code);

    int printed;

    // only escape sequences up, down, right and left
    // use an argument
    if(code < up)
        printed = fprintf(stdout, "\x1b[%s", cursor_seq[code]);

    else
        printed = fprintf(stdout, "\x1b[%d%s",
                        va_arg(arg, int), cursor_seq[code]);

    va_end(arg);

    return printed;
}

int fcursor(FILE* file, enum CursorEsc code, ...) {
    va_list arg;
    va_start(arg, code);

    int printed;

    // only escape sequences up, down, right and left
    // use an argument
    if(code < up)
        printed = fprintf(file, "\x1b[%s", cursor_seq[code]);

    else
        printed = fprintf(file, "\x1b[%d%s",
                        va_arg(arg, int), cursor_seq[code]);

    va_end(arg);

    return printed;
}
