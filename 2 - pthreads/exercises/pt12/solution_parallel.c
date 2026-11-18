#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// unsigned int GLOB_ARR[] = {14, 7, 80, 52, 20};
// in this version i think the problem is that im using two global variables, but instead of that i can use status variable of pthread join and just sum up that
// also we are using the logic i=arg, i<n, i+=T, but actually with W and N different situations <, >, = it may broke (probably will), so it is better to go with some start/end approach
#define N 268435456 //268435456
#define T 8
unsigned int GLOB_ARR[N];
unsigned int GLOB_SUM_ARR[T];
int seed = 1;

void init_vector() {
    for (long i = 0; i < N; i++) {
        GLOB_ARR[i] = rand_r(&seed) % 100;
    }
}

void *count_odds(void *arg) {
    long count = 0;
    for (long i = (long) arg; i < N; i+=T) {
        if (GLOB_ARR[i] % 2 != 0) {
            count++;
        }
    }
    GLOB_SUM_ARR[(long) arg]=count;
    return NULL;
}

void main() {
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
        pthread_join(th[i], NULL);
        sum += GLOB_SUM_ARR[i];
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

}