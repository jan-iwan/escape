#ifndef ESCAPE_H
#define ESCAPE_H

/*  #\\~                                                                ~//#  *
 *  \                                ESCAPE                                /  *
 *  /                                 v0.5                                 \  *
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
 *  Functions ending in -cf (like printfc()) will combine printf() with
 *  printc(). Any arguments for format (interpreted by printf()) need to be
 *  passed before any for color since the input string is first parsed by
 *  printf() and then by printc(). e.g `printfc("%d $n%c\n", 12, red, 'A');`.
 *  This means that `printfc("%ssome color\n", "$c3");` or even
 *  `printfc("%ssome other color color\n", "$n", blue);` will work fine.
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

// Add C++ bindings
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
#define _ESC_NARGS(...) (sizeof((int[]){0, __VA_ARGS__}) / sizeof(int) - 1)

#define ESC "\x1b["
// escape sequences supported by the printc() and color() family of functions.
// each enum value corresponds to the number inside a sequence.
// e.g. code red (value 31) maps to "\x1b[31m"
enum ESC_Color {
    // modes
    esc_reset         = 0,
    esc_bold          = 1,
    esc_dim           = 2,
    esc_italic        = 3,
    esc_underline     = 4,
    esc_blinking      = 5, // 6 is not valid
    esc_inverse       = 7,
    esc_invisible     = 8,
    esc_strikethrough = 9,

    // colors
    esc_black   = 30,
    esc_red     = 31,
    esc_green   = 32,
    esc_yellow  = 33,
    esc_blue    = 34,
    esc_magenta = 35,
    esc_cyan    = 36,
    esc_white   = 37,

    // color modifiers.
    // should be added to a color
    // e.g green + BRIGHT is bright green.
    // red + BRIGHT + BG is bright red background.
    // should not be used with modes
    esc_BG     = 10,
    esc_BRIGHT = 60,
};

// escape sequences supported by and cursor(), fcursor() and fcursorn()
enum ESC_Cursor {
    esc_wrap_on,
    esc_wrap_off,
    esc_save,
    esc_restore,
    esc_up,
    esc_down,
    esc_right,
    esc_left,
};

// write a colored string to a file
// variadic, not meant for direct use
int vfprintc(FILE* file, const char* fmt, va_list arg);

// write a formatted colored string to a file.
// arguments for format shuold be passed before any for color.
// variadic, not meant for direct use
int vfprintfc(FILE* file, const char* fmt, va_list arg);

// write a number of bytes of a colored string to a buffer
// not meant for direct use
// int vsnprintc(char* buf, size_t n, const char* fmt, va_list arg);

// write a number of bytes of formatted colored output to a buffer.
// arguments for format shuold be passed before any for color
// not meant for direct use
// int vsnprintfc(char* buf, size_t n, const char* fmt, va_list arg);

// write a colored string to a file
int fprintc(FILE* file, const char* fmt, ...);

// write a formatted colored string to a file.
// arguments for format shuold be passed before any for color
int fprintfc(FILE* file, const char* fmt, ...);

// write a colored string to stdout
int printc(const char* fmt, ...);

// print a formatted colored string.
// arguments for format shuold be passed before any for color
int printfc(const char* fmt, ...);

// write a number of escape sequence to a file
// number of argument has to be passed, not meant for direct use
int fcolorn(FILE* file, int nargs, ...);

// write escape sequences to a file
#define fcolor(file, ...) fcolorn(file, _ESC_NARGS(__VA_ARGS__), __VA_ARGS__)

// write escape sequences to a stdout.
// multiple codes can be passed. e.g. `color(red, bold)`
// #define color(...)
//     fcolorn(stdout, _ESC_NARGS(__VA_ARGS__), __VA_ARGS__)

int color(enum ESC_Color code);

/* ##  cursor movement  ## */

// write a escape sequence related to cursor control to a file.
// if moving the cursor, an additional integer can be passed
// to specify specify the distance.
// number of argument has to be passed, not meant for direct use
int fcursorn(FILE* file, enum ESC_Cursor, int nargs, ...);

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
inline enum Color operator+(enum Color color, enum Color modifier) {
    return Color((int) color + (int) modifier);
}

} /* namespace esc */
} /* extern "C" */

#endif /* __cplusplus */

#endif /* ESCAPE_H */
