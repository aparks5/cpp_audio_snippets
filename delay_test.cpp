#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"

#define BLOCKSIZE (128)
#define NCHANS (8)
#define FS (48000)

struct DelayParams
{
    size_t curDelayMs;
    size_t maxDelayMs;
};

class Delay
{
public:
    Delay(DelayParams params);
    virtual ~Delay();
    /// @brief apply processing to input to obtain output
    void run(float** in, float** out);
    /// @brief set current delay time
    void setDelayTime(size_t newDelay);
    /// @brief get current delay time
    size_t getDelayTime() const {return m_currentDelay;}
private:
    size_t m_currentDelay;
    size_t m_maxDelay;
    float** m_ppfDelayBuff;

};

Delay::Delay(DelayParams params)
    : m_currentDelay(params.curDelayMs)
    , m_maxDelay(params.maxDelayMs)
{
    m_ppfDelayBuff = new float*[NCHANS];

    for (size_t idx = 0; idx < NCHANS; idx++) {
        m_ppfDelayBuff[idx] = new float[BLOCKSIZE];
        for (size_t samp = 0; samp < BLOCKSIZE; samp++) {
            m_ppfDelayBuff[idx][samp] = 0.0f;
        }

    }
}

Delay::~Delay()
{
    for (size_t idx = 0; idx < NCHANS; idx++) {
        delete[] m_ppfDelayBuff[idx];
    }

    delete[] m_ppfDelayBuff;
    m_ppfDelayBuff = NULL;

}

void Delay::setDelayTime(size_t newDelay)
{
    if ((newDelay != m_currentDelay) || (newDelay < m_maxDelay)) {
        m_currentDelay = newDelay;
    }
}

///
/// process input with m_currentDelay output
/// @param ppfIn [input 2-d array of samples across channels]
/// @param ppfOut [output 2-d array of samples across channels]
/// @return [none]
///
void Delay::run(float** ppfIn, float** ppfOut)
{
    //assert(m_currentDelay <= m_maxDelay);

    size_t curDelaySamps = m_currentDelay*1.0f/1000*FS;

    printf("curDelaySamps: %zu\n", curDelaySamps);


    printf("INPUT BUFF:\n");
    for (size_t chan = 0; chan < 1; chan++) {
        for (size_t samp = 0; samp < 5; samp++) {
            printf("in chan: %zu, idx: %zu, val: %f \n", chan, samp, ppfIn[chan][samp]);
        }
    }

    /// delays that are smaller than the block size
    if (curDelaySamps < BLOCKSIZE) {
        /// copy some of delay buffer into output buffer
        for (size_t idx = 0; idx < 1; idx++) {
            memcpy(ppfOut[idx], m_ppfDelayBuff[idx], sizeof(float)*curDelaySamps);

            printf("POST DELAY BUFF MEMCPY\n");
            for (size_t chan = 0; chan < 1; chan++) {
                for (size_t samp = 0; samp < 5; samp++) {
                    printf("out chan: %zu, idx: %zu, val: %f \n", chan, samp, ppfOut[chan][samp]);
                }
            }


            /// copy some ,of input into output buffer
            memcpy(ppfOut[idx]+curDelaySamps, ppfIn[idx]+(idx*BLOCKSIZE), sizeof(float)*(BLOCKSIZE-curDelaySamps));

            printf("POST INPUT MEMCPY\n");
            for (size_t chan = 0; chan < 1; chan++) {
                for (size_t samp = 0; samp < 5; samp++) {
                    printf("out chan: %zu, idx: %zu, val: %f \n", chan, samp, ppfOut[chan][samp]);
                }
            }


            /// copy remaining input into delay buffer
            memcpy(m_ppfDelayBuff[idx], ppfIn[idx]+BLOCKSIZE-curDelaySamps, sizeof(float)*(curDelaySamps));
        }
    }
    else if (curDelaySamps >= BLOCKSIZE) {
        for (size_t idx = 0; idx < NCHANS; idx++) {
            /// copy delay buffer up to blocksize into the output buffer
            memcpy(ppfOut+(idx*BLOCKSIZE), &m_ppfDelayBuff[idx], sizeof(float)*BLOCKSIZE);
            /// rotate remaining delay buffer samples (note: source and destination may overlap!)
            memmove(&m_ppfDelayBuff[idx], &m_ppfDelayBuff[idx]+BLOCKSIZE, sizeof(float)*(curDelaySamps-BLOCKSIZE));
            /// copy input to delay buffer
            memcpy(&m_ppfDelayBuff[idx]+(curDelaySamps-BLOCKSIZE), ppfIn, sizeof(float)*(BLOCKSIZE));
        }
    }

}

void testDelayShorterThanBlockSize()
{
    DelayParams params = {2, 500};
    Delay m_delay(params);

    /// generate unit impulse to delay
    float** pfIn = new float*[NCHANS];
    for (size_t idx = 0; idx < NCHANS; idx++) {
        pfIn[idx] = new float[BLOCKSIZE];
        for (size_t samp = 0; samp < BLOCKSIZE; samp++) {
            pfIn[idx][samp] = 0.0f;
        }
        pfIn[idx][0] = 1.0f;
    }


    float** pfOut = new float*[NCHANS];

    for (size_t idx = 0; idx < NCHANS; idx++) {
        pfOut[idx] = new float[BLOCKSIZE];
        for (size_t samp = 0; samp < BLOCKSIZE; samp++) {
            pfOut[idx][samp] = 0.0f;
        }
    }

    // printf("prior conditions\n");
    // printf("*******************\n");
    // /// look at prior conditions
    // for (size_t chan = 0; chan < 1; chan++) {
    //     for (size_t samp = 0; samp < 5; ++samp) {
    //         printf("in chan: %zu, idx: %zu, val: %f \n", chan, samp, pfIn[chan][samp]);
    //         printf("out chan: %zu, idx: %zu, val: %f \n", chan, samp, pfOut[chan][samp]);
    //     }
    // }

    /// generate unit impulse to delay
    m_delay.run(pfIn, pfOut);

    printf("posterior conditions\n");
    printf("*******************\n");
    /// assert that unit impulse appears at expected delay time
    for (size_t chan = 0; chan < 1; chan++) {
        for (size_t samp = 90; samp < 100; samp++) {
            if (samp == 96) {
                printf("LOOK AROUND HERE -> \n");
            }
            printf("in chan: %zu, idx: %zu, val: %f \n", chan, samp, pfIn[chan][samp]);
            printf("out chan: %zu, idx: %zu, val: %f \n", chan, samp, pfOut[chan][samp]);
        }
    }

    for (size_t idx = 0; idx < NCHANS; idx++) {
        delete[] pfIn[idx];
        delete[] pfOut[idx];
    }

    delete[] pfIn;
    delete[] pfOut;

    /// here is our test
    /// assert(pfOut[chan][97] == 1.0f);

}

int main(int argc, char** argv) {
    testDelayShorterThanBlockSize();
    return 0;
}