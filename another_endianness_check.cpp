// Type your code here, or load an example.
#include "stdio.h"
#include "stdint.h"
#include "string.h"

int main(int argc, char** argv)
{
    uint32_t x = 0x1234567;
    // if we find the first byte is 0x67, that means 0x67 was stored first
    // so we are little-endian, because the least-significant byte was stored first
    printf("result: %s", 
            (*((uint8_t*)(&x)) == 0x67) ? 
            "little-endian" : "big-endian");
}