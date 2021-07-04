#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"
#include "math.h"

#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))


///
/// first-order feedback filter
/// store output in delay element
///
void feedbackFilter(float* in, float* out, size_t bufLen, float a0, float b1)
{

    float yn1 = 0.0f;
    float delay = 0.0f;

    for (size_t idx = 0; idx < bufLen; idx++) {
        yn1 = delay;
        out[idx] = a0*in[idx] - b1*yn1;
        delay = out[idx];
    }
}

void run(float* in, float* out, size_t bufLen)
{
    // create filter coefs
    float a0 = 0.5f;
    float b1 = -1.0f;

    for (size_t idx = 0; idx < bufLen; idx++) {
         feedbackFilter(in, out, bufLen, a0, b1);
    }
}


void applyGain(float fGain, float* in, size_t bufLen)
{
    printf("-------------\n");
    printf("applying gain:\n");
    for (size_t idx = 0; idx < bufLen; idx++) {
        printf("in[%d]: %f,", idx, in[idx]);
        in[idx] *= fGain;
        printf("out[%d]: %f\n", idx, in[idx]);

    }
}

int main()
{
    printf("first-order feedback filter\n");

    float dc_step[6] = {0, 0, 0, 1, 1, 1};
    float nyquist_seq[6] = {1, -1, 1, -1, 1, -1};
    float half_nyquist[6] = {1, 0, -1, 0, 1, 0};
    float quarter_nyquist[9] = {0, 0.707, 1, 0.707, 0, -0.707, -1, -0.707, 0};

    float* out = new float[128];
    memset(out, 0, sizeof(out));

    run(quarter_nyquist, out, RARRSIZE(quarter_nyquist));

    // cleanup
    delete[] out;
    return 0;
}