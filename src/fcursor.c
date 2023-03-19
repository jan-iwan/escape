#include "escape.h"

#include <stdio.h>
#include <stdarg.h>

int fcursor(FILE* file, enum Cursor code, ...) {
    va_list arg;
    va_start(arg, code);

    int printed = vfcursor(file, code, arg);

    va_end(arg);

    return printed;
}
