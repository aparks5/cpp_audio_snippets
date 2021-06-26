// Type your code here, or load an example.
#include "stdio.h"
#include "stdint.h"
#include "string.h"

int main(int argc, char** argv)
{
    int x = 1;
    printf("result: %s", 
            (char*)(x) ? 
            "little-endian" : "big-endian");

}