#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"
#include "math.h"

int main()
{
    printf("practical mixing algorithm\n");
    float in1[5] = {1,1,1,1,1};
    float in2[5] = {1,1,1,1,1};
 
    size_t nchans = 2;
    float mix[5];
    memset(mix, 0, sizeof(mix));

    float mixGain = 1.0f / nchans;
    for (size_t idx = 0; idx < (sizeof(mix)/sizeof(mix[0])); idx++) {
        mix[idx] += (mixGain*in1[idx]);
        mix[idx] += (mixGain*in2[idx]);
    }
    return 0;
}