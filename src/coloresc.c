#include "escape.h"

#include "buffer.h"
#include "variable_color.h"

int coloresc(enum ColorEsc code) {
    return fcoloresc(code, stdout);
}
