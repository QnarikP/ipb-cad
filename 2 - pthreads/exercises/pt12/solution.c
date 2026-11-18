#include <stdio.h>
#include <stdlib.h>
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
    init_vector();
    for (int i = 0; i < N; i++) {
        printf("%u ", GLOB_ARR[i]);
    }
    printf("\n");    
    int count = count_odds();
    printf("Number of odd numbers: %d\n", count);
}