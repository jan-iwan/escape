#pragma once

/*  #\\~                                                                ~//#  *
 *  \                                ESCAPE                                /  *
 *  /                                 v0.2                                 \  *
 *  \                     A library to use ANSI escape                     /  *
 *  /                           sequences easily                           \  *
 *  #\\~                                                                ~//#  */

/*
 *  TL;DR: e.g. "$c2" is green, "$cBh1" is bright red background, "$b" is bold.
 *
 *  Functions ending in -c (like printc()) which accept a format string work as
 *  follows:
 *
 *  The string may contain directives which will not be printed but rather
 *  interpreted and will cause to print an escape sequence.
 *
 *  A directive may specify a color or mode. Directives can also be variable and
 *  passed as another argument to the function.
 *
 *  '$' indicates the start of a directive, similar to '%' in printf(). "$$"
 *  prints a single '$'.
 *
 *  'c' indicated a color. The color directive has a special syntax:
 *  "$c['B']['h']<n>". <n> is a number from 0 to 7 which specifies the color
 *  where:
 *      0 - black
 *      1 - red
 *      2 - green
 *      3 - yellow
 *      4 - blue
 *      5 - magenta
 *      6 - cyan
 *      7 - white
 *  'B' stands for "Background" and indicated that the color will be set for the
 *  background rather than the foreground.
 *  'h' is for the "bright" (High) version of the color, it can be combined with
 *  'B'
 *
 *  'n' indicates a variable sequence that that is specified in a separate
 *  argument passed to the function. e.g. `printc("$n", bold);`. Any value from
 *  the Color enum can be passed as a parameter except for "BRIGHT" and "BG",
 *  which are  added (with the "+" operator) to a color. e.g.
 *  `printc("$n", green + BRIGHT);`.
 *
 *  'E' indicates an escape sequence introducer, it has the same effect as
 *  putting a literal "\x1b[" in the string.
 *
 *  All the sequences for bold, italic and similar are specified by a single
 *  character:
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
 *  Non-valid directives will be printed as they appear in the string. e.g
 *  "$abc" will print literally "$abc".
 *  
 *  A reset escape sequence will be printed at the end of the string.
 *
 *
 *  Functions ending in -cf (like printcf()) will combine printf() with
 *  printc(). Any arguments for format (interpreted by printf()) need to be
 *  passed before any for color since the input string is first parsed by
 *  printf() and then by printc(). e.g `printcf("%d $n%c\n", 12, red, 'A');`.
 *  This means that `printcf("%ssome color\n", "$c3");` or even
 *  `printcf("%ssome other color color\n", "$n", blue);` will work fine.
 *
 *
 *  The functions color() and fcolor() take a Color enum and print the
 *  corresponding escape sequence. The set color or mode won't be cleared until
 *  a reset sequence is printed specifically. A call to printc() or similar
 *  functions will print such a sequence automatically.
 *
 *
 *  The functions cursor() and fcursor() work the same as color() and fcolor()
 *  except that they take a Cursor enum as input.
*/

#ifdef __cplusplus
#include <cstdio>
#include <cstdarg>

extern "C" {
namespace esc {

#else
#include <stdio.h>
#include <stdarg.h>

#endif /* __cplusplus */

// number of variadic arguments, support for zero arguments
#define _ESC_NARGS(...) (sizeof((int[]){0, __VA_ARGS__})/sizeof(int) - 1)

#define ESC "\x1b["
// escape sequences supported by the printc() and color() family of functions.
// each enum value corresponds to the number inside a sequence.
// e.g. code red (value 31) maps to "\x1b[31m"
enum Color {
    // modes
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

    // color modifiers.
    // should be added to a color
    // e.g green + BRIGHT is bright green.
    // red + BRIGHT + BG is bright red background.
    // should not be used with modes
    BG          = 10,
    BRIGHT      = 60,
};

// escape sequences supported by and cursor(), fcursor() and fcursorn()
enum Cursor {
    wrap_on,
    wrap_off,
    save,
    restore,
    up,
    down,
    right,
    left,
};

// write a colored string to a file
// variadic, not meant for direct use
int vfprintc(FILE* file, const char* fmt, va_list arg);

// write a formatted colored string to a file.
// arguments for format shuold be passed before any for color.
// variadic, not meant for direct use
int vfprintcf(FILE* file, const char* fmt, va_list arg);

// write a number of bytes of a colored string to a buffer
// not meant for direct use
// int vsnprintc(char* buf, size_t n, const char* fmt, va_list arg);

// write a number of bytes of formatted colored output to a buffer.
// arguments for format shuold be passed before any for color
// not meant for direct use
// int vsnprintcf(char* buf, size_t n, const char* fmt, va_list arg);

// write a colored string to a file
int fprintc(FILE* file, const char* fmt, ...);

// write a formatted colored string to a file.
// arguments for format shuold be passed before any for color
int fprintcf(FILE* file, const char* fmt, ...);

// write a colored string to stdout
int printc(const char* fmt, ...);

// print a formatted colored string.
// arguments for format shuold be passed before any for color
int printcf(const char* fmt, ...);

// write a number of escape sequence to a file 
// number of argument has to be passed, not meant for direct use
int fcolorn(FILE* file, int nargs, ...);

// write escape sequences to a file
#define fcolor(file, ...) \
    fcolorn(file, _ESC_NARGS(__VA_ARGS__), __VA_ARGS__)

// write escape sequences to a stdout.
// multiple codes can be passed. e.g. `color(red, bold)`
#define color(...) \
    fcolorn(stdout, _ESC_NARGS(__VA_ARGS__), __VA_ARGS__)


/* ##  cursor movement  ## */

// write a escape sequence related to cursor control to a file.
// if moving the cursor, an additional integer can be passed
// to specify specify the distance.
// number of argument has to be passed, not meant for direct use
int fcursorn(FILE* file, enum Cursor, int nargs, ...);

// write a escape sequence related to cursor control to a file.
// if moving the cursor, an additional integer can be passed
// to specify specify the distance
#define fcursor(file, code, ...) \
    fcursorn(file, code, _ESC_NARGS(__VA_ARGS__), ##__VA_ARGS__)

// move, save or restore the position of the cursor.
// if moving the cursor, an additional integer can be passed
// to specify specify the distance
#define cursor(code, ...) \
    fcursorn(stdout, code, _ESC_NARGS(__VA_ARGS__), ##__VA_ARGS__)

#ifdef __cplusplus

// C++ would return int when adding enums and make color() not accept int
// as parameter. This overload allows to call color(red + BG)
inline enum Color operator +(enum Color color, enum Color modifier) {
    return Color((int)color + (int)modifier);
}

} /* namespace esc */
} /* extern "C" */

#endif /* __cplusplus */
