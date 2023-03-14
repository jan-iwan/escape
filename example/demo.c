#include <escape.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
    color(blue);
    puts("Some text");
    color(reset);

    const char str[] = "Hello, world!";
    for(int i = 0; i < sizeof(str); i++) {
        color((i % 6) + red);
        putchar(str[i]);
    }
    color(reset);
    putchar('\n');

    printc("$c1Red $c2Green $c4Blue\n");

    printcf("$nSome %s\n", "color", blue + BRIGHT);

    cursor(right, sizeof(str) + 2);
    for(int i = sizeof(str); i >= 0; --i) {
        color((i % 4) + green + BG);
        putchar(str[i]);

        // make the character appear immediatly
        fflush(stdout);

        usleep(50000);
        cursor(left, 2);
    }
    color(reset);
    putchar('\n');
    return 0;
}
