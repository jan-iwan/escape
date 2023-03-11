#include "escape.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "itoa.h"

#define FMT '$'
#define ESC "\x1b["
#define BUF_SIZE 512
#define FORMAT_BUF_SIZE 256

static char buffer[BUF_SIZE];
static unsigned bp; // buffer pointer

// append string literal to buffer
#define append(str)     memcpy(&buffer[bp], str, sizeof(str) - 1);\
                        (bp += sizeof(str) - 1)

// append string to buffer
#define append_str(str) register size_t len = strlen(str);\
                        memcpy(&buffer[bp], str, strlen(str));\
                        (bp += len)

// append char to buffer
#define append_char(ch) buffer[bp++] = ch;

#define MAX_ESC_LEN (sizeof(ESC "\x1b[100m") + 1)
#define LAST_USABLE_INDEX (sizeof(buffer) - MAX_ESC_LEN)

static inline int variable_color(enum ColorEsc code) {
    if(code > MAX_ESC)
        return 1;

    bp += itoa(code, &buffer[bp]);
    return 0;
}

static inline const char* color(const char* fmt) {
    unsigned bak = bp - sizeof(ESC);

    bool background = false;
    bool bright = false;

    // normal foreground by default
    append_char('3');

    char ch;
    if((ch = *fmt++) == 'B') {
            background = true;

            // replace '3' with '4'
            bp--;
            append_char('4');

            ch = *fmt++;
    }
    if(ch == 'h') {
            bright = true;

            bp--;
            if(background) {
                // replace '4' with "10"
                append_char('1');
                append_char('0');
            }
            else {
                // replace '3' with '9'
                append_char('9');
            }

            ch = *fmt++;
    }

    // color
    if(ch >= '0' && ch <= '7') {
        append_char(ch);
    }

    // invalid
    else {
        bp = bak;
        append_char(FMT);
        append_char('c');

        if(background)
            append_char('B');
        if(bright)
            append_char('h');

        append_char(ch);
    }

    return fmt;
}

int vfprintc(FILE* file, const char* fmt, va_list arg) {
    int printed = 0;
    bp = 0;

    // for "$n"
    enum ColorEsc var;

    char ch;
    while((ch = *fmt++)) {
        if(ch == FMT) {
            append(ESC);

            switch(ch = *fmt++) {
                // "$$" -> "$"
                case FMT:
                    // delete ESC
                    bp -= sizeof(ESC) - 1;

                    append_char(FMT);
                    break;

                // variable
                case 'n':
                    var = va_arg(arg, enum ColorEsc);
                    if(variable_color(var))
                        goto invalid_format;
                    goto end_escape;

                // color
                case 'c':
                    fmt = color(fmt);
                    goto end_escape;

                // reset all
                case 'r':
                    append_char('0');
                    goto end_escape;

                // bold
                case 'b':
                    append_char('1');
                    goto end_escape;


                // dim (low)
                case 'l':
                    append_char('2');
                    goto end_escape;

                // italic
                case 'i':
                    append_char('3');
                    goto end_escape;

                // underline
                case 'u':
                    append_char('4');
                    goto end_escape;

                // blinking
                case 'k':
                    append_char('5');
                    goto end_escape;

                // inverse
                case 'v':
                    append_char('6');
                    goto end_escape;

                // invisible
                case 's':
                    append_char('7');
                    goto end_escape;

                // strikethrough
                case 't':
                    append_char('8');
                    goto end_escape;


                // invalid format
                default:
                    invalid_format:
                    // delete ESC
                    bp -= sizeof(ESC) - 1;

                    append_char(FMT);
                    append_char(ch);
                    break;

                    end_escape:
                    append_char('m');
            }
        }
        else {
            append_char(ch);
        }

        // if buffer is full
        if(bp > LAST_USABLE_INDEX) {
            printed += fwrite(buffer, sizeof(char), bp, stdout);
            bp = 0;
        }
    }

    append("\x1b[0m");
    printed += fwrite(buffer, sizeof(char), bp, stdout);

    return printed;
}

int fprintc(FILE* file, const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    int printed = vfprintc(file, fmt, arg);

    va_end(arg);
    return printed;
}

int printc(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    int printed = vfprintc(stdout, fmt, arg);

    va_end(arg);
    return printed;
}

int fprintcf(FILE* file, const char* restrict fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    char format[FORMAT_BUF_SIZE];
    vsnprintf(format, sizeof(format), fmt, arg);
    int printed = vfprintc(file, format, arg);

    va_end(arg);
    return printed;
}

int printcf(const char* restrict fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    char format[FORMAT_BUF_SIZE];
    vsnprintf(format, sizeof(format), fmt, arg);
    int printed = vfprintc(stdout, format, arg);

    va_end(arg);
    return printed;
}

void fcoloresc(enum ColorEsc code, FILE* file) {
    bp = 0;
    append(ESC);
    variable_color(code);
    append_char('m');
    fwrite(buffer, sizeof(char), bp, file);
}

void coloresc(enum ColorEsc code) {
    fcoloresc(code, stdout);
}
