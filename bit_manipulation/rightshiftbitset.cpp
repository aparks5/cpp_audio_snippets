#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"
#include "math.h"

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

int getFirstSetBitPosition(int val)
{
    int pos = 1;
    while (pos < sizeof(val)*8) {
        pos++;
        if ((1 << (pos-1)) & val) {
            break;
        }
    }
    return pos;
}

int checkKthBitSetRightShift(int val, int k)
{
    return ((val >> (k-1)) & 1);
}

void findAllSubsets(int* arr, size_t arrLen)
{
   printf("num elements in arr: %d\n", arrLen); 
   printf("num possible subsets: %d\n", 2 << (arrLen-1)); 
   int nSubsets = 2 << (arrLen-1);
   for  (size_t idx = 0; idx < nSubsets; idx++)
   {

        printf("[");
        // each subset can be represented by arrLen bits
        // with 1 indicating that we should get the value at the index
        for (size_t bit = 0; bit < arrLen; bit++) {

            if ((1 << bit) & idx) {
                printf("%d",arr[bit]);
                // is this the last iteration?
                if ((1 << bit) < idx) {
                    printf(", ");
                }
            }
       }

        printf("]\n");
   }
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

    printf("------------------\n");
    printf("find all subsets of the given array:\n");
    int arr[5] = {1,2,3,4,5};
    for (size_t idx = 0; idx < (sizeof(arr)/sizeof(arr[0])); idx++) {
        printf("%d ", arr[idx]);
    }

    // printf("\n");
    // findAllSubsets(arr, static_cast<size_t>(sizeof(arr)/sizeof(arr[0])));

    printf("------------------");
    printf("find first set bit\n");
    val = 8;
    printBinary(val);
    printf("first set bit position: %d", getFirstSetBitPosition(val));

    
    printf("------------------");
    printf("check if kth bit set\n");
    val = 5;
    k = 3;
    printBinary(val);
    printf("is bit %d in val %d set? %s", k, val, (checkKthBitSetRightShift(val,k) ? "yes" : "no"));
    k = 2;
    printBinary(val);
    printf("is bit %d in val %d set? %s", k, val, (checkKthBitSetRightShift(val,k) ? "yes" : "no"));



}


