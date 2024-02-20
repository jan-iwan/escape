#include <escape.h>
#include <stdio.h>
#include <time.h>

#define ITER 0xffff

#define START   clock_gettime(CLOCK_MONOTONIC, &start)
#define END     clock_gettime(CLOCK_MONOTONIC, &end)
#define BENCH(func)   START; for(int i = 0; i < ITER; i++) func; END

#define DURATION (end.tv_nsec - start.tv_nsec)
#define TOTAL(duration) ((double)duration/1000000)

char default_test[] = "%% %d $c1 $n";

int main(int argc, char* argv[]) {
    FILE* file = fopen("/dev/null", "w");

    char* test = argc == 2 ? argv[1] : default_test ;

    struct timespec start, end;

    // fprintf
    BENCH(fprintf(file, test, argc));
    long fprintf_time = DURATION;

    // fprintc
    BENCH(fprintc(file, test, bold));
    long fprintc_time = DURATION;

    // fprintcf
    BENCH(fprintcf(file, test, argc, bold));
    long fprintcf_time = DURATION;

    BENCH(color(red));
    long color_time = DURATION;

    printcf("$c4$btest string: ");
    puts(test);
    if(test == default_test)
        printcf("$c7try %s <some string>\n",  argv[0]);

    printcf("$c3fprintf():  $c6%ld$c2ns\n", fprintf_time / ITER);
    printcf("$c5fprintc():  $c6%ld$c2ns\n", fprintc_time / ITER);
    printcf("$c1fprintcf(): $c6%ld$c2ns\n", fprintcf_time / ITER);
    printcf("$c6color(): $c6%ld$c2ns\n", color_time / ITER);

    return 0;
}
