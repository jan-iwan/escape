#include "escape.h"

#include "buffer.h"
#include "variable_color.h"

int color(enum Color code) {
    return fcolor(code, stdout);
}
