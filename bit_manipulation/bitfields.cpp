#include "stdio.h"
#include <string>
#include "math.h"

#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))

size_t getbits(uint8_t* arr, size_t arrLen, size_t* result, size_t bitPos, size_t numBits)
{

    size_t readBits = numBits;
    *result = 0;

    while (numBits > 0) {

        size_t bytePos = floor(bitPos / 8);

        if ((numBits > sizeof(size_t)*8) || (bytePos > arrLen)) {
            break;
        }
        else if (numBits > 8) {
            readBits = 8;
        }
        else if  ((bitPos % 8) + numBits > 8) {
            readBits = 8 - (bitPos % 8);
        }

        *result |= arr[bytePos] >> (8 - (bitPos % 8) - readBits) & ((1 << readBits) - 1) ;
        bitPos += readBits;
        numBits -= readBits;

        if (numBits > 0) {
            *result <<= numBits;
        } 
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
    size_t nbits = 4;
    bitpos = getbits(arr, RARRSIZE(arr), &val, bitpos, nbits);
    printf("read %d bits, pos post read %d, val %zu, expected %d\n", nbits, bitpos, val, arr[0] & 0xF);
    nbits = 2;
    bitpos = getbits(arr, RARRSIZE(arr), &val, bitpos, nbits);
    printf("read %d bits, pos post read %d, val %zu, expected %d\n", nbits, bitpos, val, arr[0] & 0x3);


    uint8_t vernum[1] = {0x3b};
    bitpos = 1;
    nbits = 4;
    bitpos = getbits(vernum, RARRSIZE(vernum), &val, bitpos, nbits);
    printf("read %d bits, pos post read %d, val %zu, expected %d\n", nbits, bitpos, val, 7);

    uint8_t dialnorm[1] = {0x80};
    bitpos = 4;
    nbits = 4;
    bitpos = getbits(dialnorm, RARRSIZE(dialnorm), &val, bitpos, nbits);
    printf("read %d bits, pos post read %d, val %zu, expected %d\n", nbits, bitpos, val, 0);
 
    return 0;
}