#include <stdio.h>

char isPrime(unsigned long n)
{
    if (n == 2 || n == 3) return 1;
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) return 0;
    for (unsigned long i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    printf("Number is: %lu\n", n);
    return 1;
}

int main(void)
{
    int counter = 0;
    unsigned long number = 1;

    while (counter < 100) {
        counter += isPrime(number);
        number++;
    }
    return 0;
}