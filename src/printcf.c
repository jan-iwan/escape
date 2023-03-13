#include "escape.h"

#include <stdio.h>
#include <stdarg.h>
#include "buffer.h"

// write a formatted colored string to stdout
int printcf(const char* fmt, ...) {
    // initialize variable arguments
    va_list arg;
    va_start(arg, fmt);

    // print formatted colored string to stdout
    int printed = vfprintcf(stdout, fmt, arg);

    va_end(arg);
    return printed;
}
