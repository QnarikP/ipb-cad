#include <stdio.h>
#include <pthread.h>

#define W 10
int COUNTER = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;


void *worker(void *arg) {
    long tid = (long) arg;

    printf("I'm the worker %ld\n", tid);
    pthread_mutex_lock(&counter_mutex);
    COUNTER ++;
    pthread_mutex_unlock(&counter_mutex);
    return NULL;
}

int main(void) {
    pthread_t th[W];
    long id;

    for (id = 0; id < W; id++) {
        pthread_create(&th[id], NULL, worker, (void *) id);
    }

    while (1) {
        if (COUNTER == W)
            break;
    }

    printf("Thread is done\n");
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}