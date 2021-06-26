#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"

#define MAX_LEN (128)
#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))

/// reverse bits in 32 bit integer

/// https://aticleworld.com/5-way-to-reverse-bits-of-an-integer/

void printBinary(uint32_t input)
{
    size_t bits = sizeof(input)*8;
    while (bits > 0) {
        int val = (input >> (bits - 1));
        // space between every nibble
        if ((bits != 32) && (bits % 4 == 0)) {
            printf(" ");
        }
        printf("%s", (val & 1) ? "1" : "0");
        bits--;
    }
    printf("\n");
}

uint32_t reverseBits(uint32_t input)
{
    uint32_t result = 0;
    printf("starting point: ");
    printBinary(result);
    size_t nbits = sizeof(input)*8;
    printf("nbits: %d\n", nbits);
    /// initialize all bits to zeros
    printBinary(input);

    for (size_t idx = 0; idx < nbits; idx++) {
        if ((input & (1 << idx))) {
            result |= (1 << (nbits - idx - 1));
        }
    }
    
    printBinary(result);
    return result;
}

int32_t reverseSignedBits(int32_t input)
{
    int32_t result = 0;
    printf("starting point: ");
    printBinary(result);
 
    size_t nbits = sizeof(input)*8;
    printf("nbits: %d\n", nbits);
    /// initialize all bits to zeros
    printBinary(input);
    
    for (size_t idx = 0; idx < nbits; idx++) {
        if ((input & (1 << idx))) {
            result |= (1 << ((nbits - 1) - idx));
        }
    }

    printBinary(result);

    return result;
}

void testUnsignedBits()
{
    /// reverse bits in unsigned 32 bit integer
    printf("reverse unsigned 32-bit int\n");
    uint32_t test = 37;
    printf("input: %d\n", test);
    printf("reversed: %u\n", reverseBits(test));

}

void testSignedBits()
{
    /// reverse bits in unsigned 32 bit integer
    printf("reverse signed 32-bit int\n");
    int32_t test = 37;
    printf("input: %d\n", test);
    printf("reversed: %d\n", reverseSignedBits(test));
}

void testShifting()
{
    printf("--------------------------\n");
    printf("test shifting\n");
    printf("test 1: \n");
    uint32_t input = 1;
    printBinary(1);
    printf("test 1 >> 1 (right shift 1): \n");
    printBinary(1 >> 1);
    printf("test 1 << 1 (left shift 1): \n");
    printBinary(1 << 1);
}

int main(int argc, char** argv)
{
    printf("-------------------------\n");
    testUnsignedBits();
    printf("-------------------------\n");
    testSignedBits();
    testShifting();
    return 0;

}

