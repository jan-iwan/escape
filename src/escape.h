#pragma once

/*  #\\~                                        ~//#  *
 *                       ESCAPE                       *
 *            A library to use ANSI escape            *
 *                  sequences easily                  *
 *  #\\~                                        ~//#  */

/*
 *  Functions like printc() which accept a format string
 *  work as follows:
 *      TL;DR: e.g. "$c2" is green, "$cBh1" is bright
 *      red background, "$b" is bold.

 *      The string may contain directives which will not
 *      be printed but rather interpreted and will cause
 *      to print an escape sequence.
 *
 *      A directive may specify or color grahic mode.
 *      Directives can also be variable and passed as
 *      another argument to the function.
 *
 *      '$' indicates the start of a directive, similar
 *      to '%' in printf(). "$$" prints a single '$'
 *
 *      'c' indicated a color. The color directive has
 *      a special syntax: "$c['B']['h']<n>", <n> is a
 *      number from 0 to 7 which specifies the color
 *      where:
 *      0 - black
 *      1 - red
 *      2 - green
 *      3 - yellow
 *      4 - blue
 *      5 - magenta
 *      6 - cyan
 *      7 - white
 *      'B' stands for "Background" and indicated that
 *      the color will be set for the background rather
 *      than the foreground.
 *      'h' is for the "brigHt" version of the color,
 *      it can be combined with 'B'
 *
 *      'n' indicates a variable sequence that that is
 *      specified in a separate argument passed to the
 *      function. e.g. `printc("$n", bold);`.
 *      any value from the ColorEsc enum can be passed
 *      as a parameter except for "BRIGHT" and "BG"
 *      ("BG" means "BackGround"), which are  added
 *      (with the "+" operator) to a color. e.g.
 *      `printc("$n", green + BRIGHT);`.
 *
 *      'E' indicates an escape sequence introducer,
 *      it has the same effect as putting a literal
 *      "\x1b[" in the string.
 *
 *      All the sequences for bold, italic and similar
 *      are specified by a single character:
 *      'r' - reset
 *      'b' - bold
 *      'l' - dim
 *      'i' - italic
 *      'u' - underline
 *      'k' - blinking
 *      'v' - inverse
 *      's' - invisible
 *      't' - strikethrough
 *
 *      Non-valid directives will be printed as they
 *      appear in the string. e.g "$abc" will print
 *      "$abc".
*/

#include <stdio.h>
#include <stdarg.h>

#define ESC "\x1b["
#define MAX_ESC (white + BRIGHT + BG)
#define FMT '$'

// escape sequences supported by printc()
enum ColorEsc {
    // graphic mode
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
    // should be added to a color
    // e.g green + BRIGHT is bright green
    // red + BRIGHT + BG is bright red background
    BG          = 10,
    BRIGHT      = 60,
};

// escape sequences supported by and cursor()
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

// write a number of bytes of a colored string to a buffer
int vsnprintc(char* buf, size_t n, const char* fmt, va_list arg);

// write a number of bytes of formatted colored output to a buffer
// arguments for format shuold be passed before any for color
int vsnprintcf(char* buf, size_t n, const char* fmt, va_list arg);

// write a colored string to a file
int vfprintc(FILE* file, const char* fmt, va_list arg);

// write a formatted colored string to a file
// arguments for format shuold be passed before any for color
int vfprintcf(FILE* file, const char* fmt, va_list arg);

// write a colored string to a file
int fprintc(FILE* file, const char* fmt, ...);

// write a formatted colored string to a file
// arguments for format shuold be passed before any for color
int fprintcf(FILE* file, const char* fmt, ...);

// write a colored string to stdout
int printc(const char* fmt, ...);

// print a formatted colored string
// arguments for format shuold be passed before any for color
int printcf(const char* fmt, ...);

// write an escape sequence to a file 
int fcoloresc(enum ColorEsc code, FILE* file);

// print an escape sequence
int coloresc(enum ColorEsc code);

// write a escape sequence related to cursor control to a file.
// if moving the cursor an integer should be passed as and
// additional parameter to specify the distance
int fcursor(FILE* file, enum CursorEsc, ...);

// move, save or restore the position of the cursor.
// if moving the cursor an integer should be passed as and
// additional parameter to specify the distance
int cursor(enum CursorEsc, ...);
