#include "escape.h"

#include "buffer.h"
#include "variable_color.h"

int fcolor(enum Color code, FILE *file) {
    bp = 0;
    append(buffer, bp, ESC);
    variable_color(buffer, &bp, code);
    append_char(buffer, bp, 'm');
    int written = fwrite(buffer, sizeof(char), bp, file);

    return written ? written : -1;
}
