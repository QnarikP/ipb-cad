#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// unsigned int GLOB_ARR[] = {14, 7, 80, 52, 20};

#define N 268435456 //268435456
unsigned int GLOB_ARR[N];
int seed = 1;

void init_vector() {
    for (int i = 0; i < N; i++) {
        GLOB_ARR[i] = rand_r(&seed) % 100;
    }
}

int count_odds() {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (GLOB_ARR[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

void main() {
    struct timespec main_begin, main_end;
    struct timespec count_begin, count_end;

    clock_gettime(CLOCK_REALTIME, &main_begin);

    init_vector();

    clock_gettime(CLOCK_REALTIME, &count_begin);
    int count = count_odds();
    clock_gettime(CLOCK_REALTIME, &count_end);

    printf("Number of odd numbers: %d\n", count);

    clock_gettime(CLOCK_REALTIME, &main_end);

    long main_seconds = main_end.tv_sec - main_begin.tv_sec;
    long main_nanoseconds = main_end.tv_nsec - main_begin.tv_nsec;
    long time_main = main_seconds * 1000000000L + main_nanoseconds;

    long count_seconds = count_end.tv_sec - count_begin.tv_sec;
    long count_nanoseconds = count_end.tv_nsec - count_begin.tv_nsec;
    long time_count = count_seconds * 1000000000L + count_nanoseconds;

    printf("time main (ns): %ld\n", time_main);
    printf("time count_odds (ns): %ld\n", time_count);
}
