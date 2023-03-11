#include "escape.h"

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

void fcursor(FILE* file, enum CursorEsc code, int d) {
    // only escape sequences up, down, right and left
    // use an argument
    if(code < up)
        fprintf(file, "\x1b[%s", cursor_seq[code]);

    else
        fprintf(file, "\x1b[%d%s", d, cursor_seq[code]);
}

void cursor(enum CursorEsc code, int d) {
    fcursor(stdout, code, d);
}
