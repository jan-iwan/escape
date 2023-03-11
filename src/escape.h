#pragma once

#include <stdio.h>
#include <stdarg.h>

#define MAX_ESC (white + BRIGHT + BG)

// all the escape sequences supported by vfprintc()
enum ColorEsc {
    // graphics
    reset       = 0,
    bold        = 1,
    dim         = 2,
    italic      = 3,
    underline   = 4,
    blinking    = 5,
    // invalid  = 6,
    inverse     = 7,
    invisible   = 8,
    strikethrough = 9,

    // colors
    black       = 30,
    red         = 31,
    green       = 32,
    yellow      = 33,
    blue        = 34,
    magenta     = 35,
    cyan        = 36,
    white       = 37,

    // color modifiers
    BG          = 10,
    BRIGHT      = 60,
};

// all escape sequences supported by fcursor()
enum CursorEsc {
    wrap_on,
    wrap_off,
    save,
    restore,
    up,
    down,
    right,
    left,
};

// print colored output to file
// writes up to 512 characters (invluding escape sequences)
int vfprintc(FILE* file, const char* fmt, va_list arg);

// print colored output to file
// writes up to 512 characters (invluding escape sequences)
int fprintc(FILE* file, const char* fmt, ...);

// print colored output to stdout
// writes up to 512 characters (invluding escape sequences)
int printc(const char* fmt, ...);

// print colored, formatted output to file
// writes up to 512 characters (invluding escape sequences)
// reads up to 256 characters from formatted string
int fprintcf(FILE* file, const char* fmt, ...);

// print colored, formatted output to stdout
// writes up to 512 characters (invluding escape sequences)
// reads up to 256 characters from formatted string
int printcf(const char* fmt, ...);

// print escape sequence to file
void fcoloresc(enum ColorEsc code, FILE* file);

// print escape sequence to stdout
void coloresc(enum ColorEsc code);

// print escape sequence realted to the cursor to file
void fcursor(FILE* file, enum CursorEsc code, int d);

// print escape sequence realted to the cursor to stdout
void cursor(enum CursorEsc code, int d);
