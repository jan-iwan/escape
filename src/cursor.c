#include "escape.h"

#include <stdio.h>
#include <stdarg.h>

int cursor(enum Cursor code, ...) {
    va_list arg;
    va_start(arg, code);

    int printed = vfcursor(stdout, code, arg);

    va_end(arg);

    return printed;
}
