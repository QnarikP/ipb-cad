/*
shared:
    STATUSES[0 .. W-1]
    mutex
    cond

worker(tid):
    print "I'm the worker tid"
    lock(mutex)
    STATUSES[tid] = 1
    signal(cond)          // "look again", even if others are still 0
    unlock(mutex)

main:
    for i in 0 .. W-1:
        STATUSES[i] = 0
        start worker(i)

    lock(mutex)
    while some STATUSES[i] is 0:      // this is the check
        wait(cond, mutex)              // drop mutex, sleep, lock it again
    unlock(mutex)

    print "done"
*/
#include <stdio.h>
#include <pthread.h>

#define W 10

int STATUSES[W];
pthread_mutex_t mutex_main = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_main = PTHREAD_COND_INITIALIZER;

void *worker(void *arg) {
    long tid = (long) arg;

    printf("I'm the worker %ld\n", tid);
    pthread_mutex_lock(&mutex_main);
    STATUSES[tid] = 1;
    pthread_cond_signal(&cond_main);
    pthread_mutex_unlock(&mutex_main);

    return NULL;
}

int main(void) {
    pthread_t th[W];
    long id;

    for (id = 0; id < W; id++) {
        STATUSES[id] = 0;
        pthread_create(&th[id], NULL, worker, (void *) id);
    }

    pthread_mutex_lock(&mutex_main);
    while (1) {
        int mlt = 1;

        for (id = 0; id < W; id++) {
            mlt *= STATUSES[id];
            if (mlt == 0)
                break;
        }
        if (mlt == 1)
            break;

        pthread_cond_wait(&cond_main, &mutex_main);
    }
    pthread_mutex_unlock(&mutex_main);

    printf("Thread is done\n");
    return 0;
}