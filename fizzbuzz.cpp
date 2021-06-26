#include "stdio.h"
#include "stdint.h"
#include "stddef.h"

// Write a program that prints the numbers from 1 to 100.
// But for multiples of three print “Fizz” instead of the number 
// and for the multiples of five print “Buzz”. 
int main(int argc, char** argv)
{

    for (size_t idx = 1; idx <= 100; idx++) {
        if ((idx % 15 == 0)) {
            printf("FizzBuzz\n");
        }
        else if ((idx % 3) == 0) {
            printf("Fizz\n");
        }
        else if ((idx % 5) == 0) {
            printf("Buzz\n");
        }
        else {
            printf("%d\n", idx);
        }
    }
    return 0;
}
