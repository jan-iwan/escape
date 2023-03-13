#include "escape.h"

#include <stdio.h>
#include <stdarg.h>
#include "buffer.h"

char format_buffer[FMT_BUF_SIZE];

// write a number of bytes of formatted colored output to a buffer
int vsnprintcf(char* buf, size_t n, const char* fmt, va_list arg) {
    // write formatted output to format_buffer
    // return if there is an error
    if(vsnprintf(format_buffer, FMT_BUF_SIZE, fmt, arg) < 0)
        return -1;

    // write colored output to buf
    return vsnprintc(buf, n, format_buffer, arg);
}
