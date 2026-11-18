#include <stdio.h>
#include <pthread.h>

#define W 10

int STATUSES[W];

void *worker(void *arg) {
    long tid = (long) arg;

    printf("I'm the worker %ld\n", tid);
    STATUSES[tid] = 1;
    return NULL;
}

int main(void) {
    pthread_t th[W];
    long id;

    for (id = 0; id < W; id++) {
        STATUSES[id] = 0;
        pthread_create(&th[id], NULL, worker, (void *) id);
    }

    while (1) {
        int mlt = 1;

        for (id = 0; id < W; id++) {
            mlt *= STATUSES[id];
            if (mlt == 0)
                break;
        }
        if (mlt == 1)
            break;
    }

    printf("Thread is done\n");
    return 0;
}