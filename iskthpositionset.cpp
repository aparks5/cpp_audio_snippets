#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"

void printBinary(int val)
{
    size_t nbits = sizeof(val)*8;
    printf("binary of %d:\n", val);

    printf("little-endian:\n");
    for (size_t idx = 0; idx < nbits; idx++) {
        printf("%s", (idx % 4 == 0) ? " " : "");
        printf("%d", ((val >> (nbits-idx-1)) & 1) ? 1 : 0);
    }
 
    printf("\n");
}

// answers: how many bits deep do we have to go before we exceed the value?
int countBitLength(int val)
{
    int len = 0;
    while ((1 << len) < val) {
        len++;
    }
    return len;
}

/// assuming k is indexed to 1 implying the "first bit"
bool isKBitSet(int val, int k)
{
    return val & (1 << (k - 1)); 
}


int main()
{
    int val = 15;
    printBinary(val);
    printf("number of bits required: %d\n", countBitLength(val));
    printf("\n");

    val = 19384;
    printBinary(val);
    printf("num bits required: %d\n", countBitLength(val));

    val = 15;
    int k = 3;
    printBinary(val);
    printf("is bit position %d of %d set? %s\n", k, val, isKBitSet(val,k) ? "yes" : "no");

    val = 15;
    k = 5;
    printBinary(val);
    printf("is bit position %d of %d set? %s\n", k, val, isKBitSet(val,k) ? "yes" : "no");


}


