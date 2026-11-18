#include <stdio.h>
#include <math.h>
#include <pthread.h>


#define K 1000000
#define W 4
double partial[W];

double sum(int k)
{
    return 4 * (pow(-1, k) / (2 * k + 1));
}

void* worker(void *arg)
{
    long k = (long)arg;
    double my_sum = 0;
    for (int i = k; i < K; i += W)
        my_sum += sum(i);
    partial[k] = my_sum;
    return NULL;
}

int main()
{
    double pi = 0;
    pthread_t th[W];
    for (long t = 0; t < W; t++)
        pthread_create(&th[t], NULL, worker, (void *)t);
    for (int t = 0; t < W; t++)                 
        pthread_join(th[t], NULL);
    for (int t = 0; t < W; t++)                 
        pi += partial[t];

    printf("pi   = %.15f\n", pi);
    printf("M_PI = %.15f\n", M_PI);
    printf("diff = %e\n", pi - M_PI);
    return 0;
}   
