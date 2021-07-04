// Type your code here, or load an example.
#include "stdio.h"
#include "stdint.h"
#include "string.h"


size_t fib(int n)
{
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else {
        return  fib(n-1) + fib(n-2);
    }
}
int main(int argc, char** argv)
{
    // print n terms of fibonacci sequence


    size_t n = 10;

    printf("first %d terms of fibonacci sequence\n", n);

    for (size_t idx = 0; idx < n; ++idx) {
        size_t result = fib(idx);
        printf("%d\n", result);
    }
}