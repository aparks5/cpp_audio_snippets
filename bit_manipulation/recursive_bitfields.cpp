// Type your code here, or load an example.
#include "stdio.h"
#include <string>
#include "math.h"

using namespace std;

#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))

size_t getbits(uint8_t* arr, size_t arrLen, size_t* result, size_t bitPos, size_t numBits)
{
    if ((numBits > sizeof(size_t)*8) || (bitPos/8 > arrLen)) {
        return bitPos;
    }

    size_t readBits = numBits;
    if (numBits > 8) {
        readBits = 8;
    }

    size_t bytePos = floor(bitPos / 8);
    *result |= arr[bytePos] >> (8 - (bitPos % 8) - readBits) & ((1 << readBits) - 1) ;
    bitPos += readBits;
    numBits -= readBits;

    if (numBits > 0) {
        *result <<= numBits;
        return getbits(arr, arrLen, result, bitPos, numBits);
    }

    return bitPos;
}


int main() {
    uint8_t arr[4] = {0xFF,0xFF,0xFF,0xFF};
    for (size_t idx = 0; idx < 4; idx++) {
        printf("val idx %d: %d\n", idx, arr[idx]);
    }

    size_t val = 0;
    size_t bitpos = 0;
    bitpos = getbits(arr, RARRSIZE(arr), &val, bitpos, 4);
    printf("value of first 4 bits: %d, pos after reading 4 bits: %zu, expected %d\n", val, bitpos, arr[0]);
    // have to clear value after extracting
    val = 0;
    bitpos = getbits(arr, RARRSIZE(arr), &val, bitpos, 2);
    printf("value of first 2 bits: %d, pos after reading 2 bits: %zu, expected %d", val, bitpos, arr[0] & 0xF);
    return 0;
}