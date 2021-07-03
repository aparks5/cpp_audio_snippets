#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"

void printBinary(int val)
{
    size_t nbits = sizeof(val)*8;
    printf("binary of %d:\n", val);
    // big endian representation
    printf("big-endian:\n");
    for (size_t idx = 0; idx < nbits; idx++) {
        printf("%d", ((val >> idx) & 1) ? 1 : 0);
    }

    printf("\n");
    printf("little-endian:\n");
    for (size_t idx = 0; idx < nbits; idx++) {
        printf("%d", ((val >> (nbits-idx-1)) & 1) ? 1 : 0);
    }
 
    printf("\n");
}

size_t countSetBitsNaive(int val)
{
    size_t setBits = 0;
    while (val) {
        setBits++;
        val >>= 1;
    }
    return setBits;
}

// Kernighan's algorithm
size_t countSetBitsKern(int val)
{
    size_t setBits = 0;
    while (val) {
        setBits++;
        val &= (val-1);
    }
    return setBits;
}

int main()
{
    int val = 15;
    printBinary(val);
    printf("set bits: %d\n", countSetBitsNaive(val));
    printf("set bits: %d\n", countSetBitsKern(val));
}


