#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"
#include "math.h"

#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))

void hp_filter(float coef, float in, float* out, float* delay)
{
    // y[n] = (a1-1)*x[n] + (a1)*x[n-1]
    *out = ((coef-1.0f)*in) + (coef*(*delay));
    *delay = in;
}

void run(float* in, float* out, size_t bufLen)
{
    float coef = 0.5f;
    float delay = 0.0f;

    for (size_t idx = 0; idx < bufLen; idx++) {
        hp_filter(coef, in[idx], &out[idx], &delay);
        printf("in %f, out %f, delay %f\n", in[idx], out[idx], delay);
    }

}

int main()
{
    printf("one-sample highpass filter\n");

    float dc_step[6] = {0, 0, 0, 1, 1, 1};
    float nyquist_seq[6] = {1, -1, 1, -1, 1, -1};
    float half_nyquist[6] = {1, 0, -1, 0, 1, 0};
    float quarter_nyquist[9] = {0, 0.707, 1, 0.707, 0, -0.707, -1, -0.707, 0};

    size_t bufLen = RARRSIZE(dc_step);
    float* out = new float[bufLen];
    memset(out, 0, sizeof(out));

    run(dc_step, out, bufLen);

    delete[] out;

    return 0;
}