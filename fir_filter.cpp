// Type your code here, or load an example.
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "math.h"

#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define BLOCKSIZE (128)
#define NTAPS (16)
///
/// Filter in with FIR filter kernel h of length ntaps.
/// convolution in the time domain:
/// y[n] = sum_i(h[n-i]*x[i])
/// in freq domain, multiplication is the equivalent of convolution in the time domain
/// Y[n] = fft(x)*fft(h)
/// @param h [filter kernel]
/// @param ntaps [number of taps in FIR filter]
/// @param in [input buffer]
/// @param out [output buffer to write]
/// @return [none]
///
void fir_filter(const float* h, const float* in, float* out)
{

    for (size_t idx = 0; idx < BLOCKSIZE; idx++) {
        for (size_t jdx = 0; jdx < NTAPS; jdx++) {
            out[idx] += h[jdx] * in[idx];
        }
    }

}

int main(int argc, char** argv)
{

    /// filter impulse reponse
    float h[NTAPS];
    memset(h, 0, sizeof(h)/sizeof(h[0]));
    h[0] = 1.0;
    size_t ntaps = NTAPS;


    float in[BLOCKSIZE];
    float out[BLOCKSIZE];
    memset(in, 0, RARRSIZE(in));
    memset(out, 0, RARRSIZE(in));

    // input frequency
    float freq = 500;
    // sample rate
    float fs = 44100;

    /// fill input with sine wave
    for (size_t idx = 0; idx < RARRSIZE(in); idx++) {
        in[idx] = sin(2*3.14157*idx*(1/fs)*freq);
    }

    fir_filter(h, in, out);

    printf("filter kernel \n");
    size_t testLen = 5;
    for (size_t idx = 0; idx < testLen; idx++) {
        printf("idx %zu, value %f\n", idx, h[idx]);
    }
    printf("input samples \n");
    for (size_t idx = 0; idx < testLen; idx++) {
        printf("idx %zu, value %f\n", idx, in[idx]);
    }

    printf("output samples \n");
    for (size_t idx = 0; idx < testLen; idx++) {
        printf("idx %zu, value %f\n", idx, out[idx]);
    }
}