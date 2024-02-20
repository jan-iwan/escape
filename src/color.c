#include "escape.h"

#include "variable_color.h"

int color(enum Color code) {
    bp = 0;
    append(ESC);
    variable_color(code);
    append_char('m');
    int written = fwrite(buffer, sizeof(char), bp, stdout);

    return written ? written : -1;
} 
