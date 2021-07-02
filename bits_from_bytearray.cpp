#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"

int extractKBits(const uint8_t* arr, uint8_t nbits, uint8_t startbit)
{
    uint8_t idx = startbit >> 3;
    printf("idx: %d\n", idx);
    return ((1 << nbits) - 1) & (arr[idx] >> (startbit % 8));
}


int main()
{
    int res = 0;

    uint8_t in[5] = {1,0,1,0,1}; 
    printf("result: %d\n", res);
    printf("----\n");
    printf("first four bits: %d\n", extractKBits(in, 4, 3));
    printf("second four bits: %d\n", extractKBits(in, 4, 8));
    printf("third four bits: %d\n", extractKBits(in, 4, 16));
    printf("fourth four bits: %d\n", extractKBits(in, 4, 24));
    printf("fifth four bits: %d\n", extractKBits(in, 4, 32));
    return 0;
}


