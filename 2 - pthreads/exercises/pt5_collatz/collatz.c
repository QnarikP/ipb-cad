#include <stdio.h>

long long p;

void main(void) {
    printf("Enter a number: ");
    scanf("%lld", &p);
    while (p!=1) {
        if (p % 2 == 0) {
            p = p / 2;
        } else {
            p = 3 * p + 1;
        }
        printf("%lld\n", p);
    }
}