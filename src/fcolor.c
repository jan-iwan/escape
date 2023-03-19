#include "escape.h"

#include "buffer.h"
#include "variable_color.h"

int fcolor(enum Color code, FILE *file) {
    bp = 0;
    append(ESC);
    variable_color(code);
    append_char('m');
    int written = fwrite(buffer, sizeof(char), bp, file);

    return written ? written : -1;
}
