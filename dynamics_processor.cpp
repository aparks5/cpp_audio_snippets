#include "stddef.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define BLOCKSIZE (128)

struct DynamicsProcessorParams
{
   size_t attackTimeMs;
   size_t decayTimeMs;
   float ratio;
   float kneeDb;
   float thresholdDb;
};

class DynamicsProcessor
{
public:
    DynamicsProcessor(DynamicsProcessorParams params);
    virtual ~DynamicsProcessor();
    void run(float* inBuff, float* outBuff);

private:
    DynamicsProcessorParams m_params;
    float m_gaindB; // gain to apply to signal

    void applyGain(float* inBuff);


};

void DynamicsProcessor::applyGain(float* inBuff)
{
    float scaleFactor = pow(10.0f,m_gaindB/20.0f);

    for (size_t samp = 0; samp < BLOCKSIZE; samp++) {
        inBuff[samp] *= scaleFactor;
    }
}

static float calcRMSdB(float* inBuff, size_t bufLen)
{
    float accum = 0.0f;

    // square samples
    for (size_t samp = 0; samp < bufLen; samp++) {
        accum += samp*samp;          
    }

    // calculate dB rms
    return ((!accum) ? -144.0f : 20*log10(sqrt(accum/bufLen)));
}

bool testAttackTime()
{
    /// measure slope over duration
    return true;
}

int main(int argc, char** argv)
{
    printf("dynamics processor");
    return 0;
}
