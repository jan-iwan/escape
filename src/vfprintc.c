#include "escape.h"

#include <stdio.h>
#include <stdarg.h>
#include "buffer.h"

char buffer[BUF_SIZE];
unsigned bp;

// write a colored string to a file
int vfprintc(FILE* file, const char* fmt, va_list arg) {
    // write colored output to buffer
    int printed = vsnprintc(buffer, BUF_SIZE, fmt, arg);

    // if there was an error return -1
    if(printed == -1) 
        return -1;

    // write buffer to file
    int written = fwrite(buffer, sizeof(char), printed, file);

    // if there was an error return -1, if not return written
    return written == printed ? written : -1;
}
