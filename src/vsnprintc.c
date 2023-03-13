#include "escape.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "buffer.h"
#include "variable_color.h"
// #include "color.h"

#define MAX_ESC_LEN (sizeof(ESC "\x1b[100m") + 1)
#define BUF_LIMIT (n - MAX_ESC_LEN)

// avoid passing the buffer as parameter to color()
// and passing bufptr by reference
char* buf;
unsigned bufptr;

static inline const char* color(const char* fmt) {
    unsigned bak = bufptr - sizeof(ESC);

    bool background = false;
    bool bright = false;

    // normal foreground by default
    append_char(buf, bufptr, '3');

    char ch = *fmt++;
    if(ch == 'B') {
            background = true;

            // replace '3' with '4'
            bufptr--;
            append_char(buf, bufptr, '4');

            ch = *fmt++;
    }
    if(ch == 'h') {
            bright = true;

            bufptr--;
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
        bufptr = bak;
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

int vsnprintc(char* outbuf, size_t n, const char* fmt, va_list arg) {
    // set global variables
    buf = outbuf;
    bufptr = 0;

    // for "$n"
    enum ColorEsc var;

    char ch;
    while((ch = *fmt++) && bufptr < BUF_LIMIT) {
        if(ch == FMT) {
            append(buf, bufptr, ESC);

            switch(ch = *fmt++) {
                // "$$" -> "$"
                case FMT:
                    // delete ESC
                    bufptr -= sizeof(ESC) - 1;

                    append_char(buf, bufptr, FMT);
                    break;

                // variable (can be anything)
                case 'n':
                    var = va_arg(arg, enum ColorEsc);
                    if(variable_color(buf, &bufptr, var))
                        goto invalid_format;
                    goto end_escape;

                // color
                case 'c':
                    fmt = color(fmt);
                    goto end_escape;

                /* graphic mode */

                // reset all
                case 'r':
                    append_char(buf, bufptr, '0');
                    goto end_escape;

                // bold
                case 'b':
                    append_char(buf, bufptr, '1');
                    goto end_escape;


                // dim (low)
                case 'l':
                    append_char(buf, bufptr, '2');
                    goto end_escape;

                // italic
                case 'i':
                    append_char(buf, bufptr, '3');
                    goto end_escape;

                // underline
                case 'u':
                    append_char(buf, bufptr, '4');
                    goto end_escape;

                // blinking
                case 'k':
                    append_char(buf, bufptr, '5');
                    goto end_escape;

                // inverse
                case 'v':
                    append_char(buf, bufptr, '6');
                    goto end_escape;

                // invisible
                case 's':
                    append_char(buf, bufptr, '7');
                    goto end_escape;

                // strikethrough
                case 't':
                    append_char(buf, bufptr, '8');
                    goto end_escape;

                // sequence introducer
                case 'E':
                    append_char(buf, bufptr, '[');
                    break;

                // invalid format
                default:
                    invalid_format:
                    // delete ESC
                    bufptr -= sizeof(ESC) - 1;

                    append_char(buf, bufptr, FMT);
                    append_char(buf, bufptr, ch);
                    break;

                    end_escape:
                    // add 'm' to terminate valid sequences
                    append_char(buf, bufptr, 'm');
            }
        }
        else {
            append_char(buf, bufptr, ch);
        }
    }

    append(buf, bufptr, "\x1b[0m");

    return bufptr;
}
