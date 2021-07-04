#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"

#define MAX_LEN (128)
#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
// Write a program that prints the numbers from 1 to 100.
// But for multiples of three print “Fizz” instead of the number 
// and for the multiples of five print “Buzz”. 
int main(int argc, char** argv)
{
    // find missing number
    int arr[] = {1, 2, 4, 6, 3, 7, 8};
    bool bExists = false;

    for (size_t idx = 1; idx <= 8; idx++) {
        for (size_t jdx = 0; jdx < RARRSIZE(arr); jdx++) {
            if (arr[jdx] == idx) {
                bExists = true;
            }
        }
        if (!bExists) {
            printf("missing element: %d\n", idx);
        }
        bExists = false;
    }
    return 0;
}
