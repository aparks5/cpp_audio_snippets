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
    // upper limit is 0.49 for this filter
    float coef = 0.49f;

    // clamp value
    coef = (coef > 0.49f) ? 0.49 : coef;

    float delay = 0.0f;

    for (size_t idx = 0; idx < bufLen; idx++) {
        hp_filter(coef, in[idx], &out[idx], &delay);
        printf("in %f, out %f, delay %f\n", in[idx], out[idx], delay);
    }

}


float dBtoFloatGain(int db)
{
    return pow(10.0f, db/20.0f);
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
    printf("one-sample highpass filter\n");

    float dc_step[6] = {0, 0, 0, 1, 1, 1};
    float nyquist_seq[6] = {1, -1, 1, -1, 1, -1};
    float half_nyquist[6] = {1, 0, -1, 0, 1, 0};
    float quarter_nyquist[9] = {0, 0.707, 1, 0.707, 0, -0.707, -1, -0.707, 0};

    float* out = new float[128];
    memset(out, 0, sizeof(out));

    printf("DC step sequence:\n");
    run(dc_step, out, RARRSIZE(dc_step));
    printf("--------------------\n");

    printf("quarter nyquist sequence:\n");
    run(quarter_nyquist, out, RARRSIZE(quarter_nyquist));
    printf("--------------------\n");




    // add volume scaling after processing
    printf("volume conversions:\n");
    int vol = -30; 
    printf("volume %d dB to float gain: %f\n", vol, dBtoFloatGain(vol));
    vol = -20; 
    printf("volume %d dB to float gain: %f\n", vol, dBtoFloatGain(vol));
    vol = -10; 
    printf("volume %d dB to float gain: %f\n", vol, dBtoFloatGain(vol));
    vol = 0; 
    printf("volume %d dB to float gain: %f\n", vol, dBtoFloatGain(vol));
    vol = 10; 
    printf("volume %d dB to float gain: %f\n", vol, dBtoFloatGain(vol));

    applyGain(dBtoFloatGain(-10), out, RARRSIZE(quarter_nyquist));


    delete[] out;
    return 0;
}