#include <escape.h>
#include <stdio.h>
#include <time.h>

#define ITER 0xffff

#define START   clock_gettime(CLOCK_MONOTONIC, &start)
#define END     clock_gettime(CLOCK_MONOTONIC, &end)
#define BENCH(func)   START; for(int i = 0; i < ITER; i++) func; END

#define DURATION ((double)(end.tv_nsec - start.tv_nsec) / 1000000)

#define TEST "%% %d $c1 $n"

int main(int argc, char* argv[]) {
    char* path = argc > 1 ? argv[1] : "/dev/null";
    FILE* file = fopen(path, "w");

    struct timespec start, end;

    // fprintf
    BENCH(fprintf(file, TEST, argc));
    double fprintf_time = DURATION;

    // fprintc
    BENCH(fprintc(file, TEST, bold));
    double fprintc_time = DURATION;

    // fprintcf
    BENCH(fprintcf(file, TEST, argc, bold));
    double fprintcf_time = DURATION;

    printcf("$c3fprintf():  $c6%.4f$c2ms\n", fprintf_time);
    printcf("$c5fprintc():  $c6%.4f$c2ms\n", fprintc_time);
    printcf("$c1fprintcf(): $c6%.4f$c2ms\n", fprintcf_time);
    return 0;
}
