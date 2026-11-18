#include <stdio.h>

// Tn = n(n+1)/2

int main(void) {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("The %dth triangular number is %d\n", n, sum);   
    return sum;
}