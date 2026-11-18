#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void *collatz(void *arg) {
    unsigned int seed;
    long long pbak, p;
    seed = pthread_self();
    pbak = p = rand_r(&seed);
    // p = 14;
    printf("thread id: %ld, initial value of p: %lld\n", seed, p);
    while (p!=1) {
        if (p % 2 == 0) {
            p = p / 2;
        } else {
            p = 3 * p + 1;
        }
        printf("%lld\n", p);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[10];
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  
    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, collatz, (void *)numbers[i]);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
