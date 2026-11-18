#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
// unsigned int GLOB_ARR[] = {14, 7, 80, 52, 20};
// partial count comes back from pthread_join
// each thread gets a start/end block
// init stays serial, same as the baseline. the sheet's ideal speedup only counts count_odds as parallel work
#define N 268435456 //268435456
int T = 8;
unsigned int GLOB_ARR[N];
int seed = 1;

void init_vector() {
    for (long i = 0; i < N; i++) {
        GLOB_ARR[i] = rand_r(&seed) % 100;
    }
}

void *count_odds(void *arg) {
    long tid = (long) arg;
    long chunk = N / T;
    long start = tid * chunk;
    long end = (tid == T - 1) ? N : start + chunk;
    long count = 0;

    for (long i = start; i < end; i++) {
        if (GLOB_ARR[i] % 2 != 0) {
            count++;
        }
    }
    return (void *) count;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        T = atoi(argv[1]);
    }

    struct timespec main_begin, main_end;
    struct timespec count_begin, count_end;

    clock_gettime(CLOCK_REALTIME, &main_begin);

    init_vector();

    // for (long i = 0; i < N; i++) {
    //     printf("%u ", GLOB_ARR[i]);
    // }
    clock_gettime(CLOCK_REALTIME, &count_begin);

    pthread_t th[T];

    for (long i=0; i<T; i++){
        pthread_create(&th[i], NULL, count_odds, (void*)i);
    }
    long sum = 0;
    for (int i=0; i<T; i++){
        void *ret;
        pthread_join(th[i], &ret);
        sum += (long) ret;
    }
    clock_gettime(CLOCK_REALTIME, &count_end);

    printf("\n");
    printf("Number of odd numbers: %ld\n", sum);
    printf("N = %d\n", N);
    printf("Theards %d\n", T);
    clock_gettime(CLOCK_REALTIME, &main_end);


    long main_seconds = main_end.tv_sec - main_begin.tv_sec;
    long main_nanoseconds = main_end.tv_nsec - main_begin.tv_nsec;
    long time_main = main_seconds * 1000000000L + main_nanoseconds;

    long count_seconds = count_end.tv_sec - count_begin.tv_sec;
    long count_nanoseconds = count_end.tv_nsec - count_begin.tv_nsec;
    long time_count = count_seconds * 1000000000L + count_nanoseconds;

    printf("time main (ns): %ld\n", time_main);
    printf("time count_odds (ns): %ld\n", time_count);

    return 0;
}
