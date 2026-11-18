#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// unsigned int GLOB_ARR[] = {14, 7, 80, 52, 20};
// in this version i think the problem is that im using two global variables, but instead of that i can use status variable of pthread join and just sum up that
// also we are using the logic i=arg, i<n, i+=T, but actually with W and N different situations <, >, = it may broke (probably will), so it is better to go with some start/end approach
#define N 268435456 //268435456
// #define T 8
int T;
unsigned int GLOB_ARR[N];
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
    return (void*)count;
}

int main(int argc, char **argv) {
    T = atoi(argv[1]);
    void *status;
    printf("Number of arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
            
    init_vector();
    // for (long i = 0; i < N; i++) {
    //     printf("%u ", GLOB_ARR[i]);
    // }

    pthread_t th[T];
    for (long i=0; i<T; i++){
        pthread_create(&th[i], NULL, count_odds, (void*)i);
    }
    long sum = 0;
    for (int i=0; i<T; i++){
        pthread_join(th[i], &status);
        sum += (long) status;
    }

    printf("\n");    
    printf("Number of odd numbers: %ld\n", sum);
    printf("N = %d\n", N);
    printf("Theards %d\n", T);


}