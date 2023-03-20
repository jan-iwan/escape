#include <escape.h>
#include <stdio.h>
#include <time.h>

#define ITER 0xffff

#define START   clock_gettime(CLOCK_MONOTONIC, &start)
#define END     clock_gettime(CLOCK_MONOTONIC, &end)
#define BENCH(func)   START; for(int i = 0; i < ITER; i++) func; END

#define DURATION ((double)(end.tv_nsec - start.tv_nsec) / 1000000)

char default_test[] = "%% %d $c1 $n";

int main(int argc, char* argv[]) {
    FILE* file = fopen("/dev/null", "w");

    char* test = argc == 2 ? argv[1] : default_test ;

    struct timespec start, end;

    // fprintf
    BENCH(fprintf(file, test, argc));
    double fprintf_time = DURATION;

    // fprintc
    BENCH(fprintc(file, test, bold));
    double fprintc_time = DURATION;

    // fprintcf
    BENCH(fprintcf(file, test, argc, bold));
    double fprintcf_time = DURATION;

    printcf("$c4$btest string: ");
    puts(test);
    if(test == default_test)
        printcf("$c7try %s <some string>\n",  argv[0]);

    printcf("$c3fprintf():  $c6%.4f$c2ms\n", fprintf_time);
    printcf("$c5fprintc():  $c6%.4f$c2ms\n", fprintc_time);
    printcf("$c1fprintcf(): $c6%.4f$c2ms\n", fprintcf_time);
    return 0;
}
