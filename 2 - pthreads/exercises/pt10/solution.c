#include <stdio.h>
#include <math.h>
double sum(int k)
{
    return 4 * (pow(-1, k) / (2 * k + 1));
}
int main()
{ 
    int k;
    double pi = 0;
    for (k = 0; k < 100000; k++){
        pi += sum(k);
    }
    printf("%f\n", pi);
    printf("%f\n", M_PI);
    printf("The difference is %f\n", pi - M_PI);
    return 0;
}

