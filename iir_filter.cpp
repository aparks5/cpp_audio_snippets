// Type your code here, or load an example.
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "math.h"
#include "stddef.h"

#define SAMPLING_FREQUENCY (48000)
#define BLOCKSIZE (128)
#define NCHANS (2)

enum FilterType
{
    FILTER_LOWPASS,
    FILTER_HIGHPASS,
    FILTER_BANDPASS,
    FILTER_LOWSHELF,
    FILTER_HIGHSHELF,
    FILTER_BANDSTOP
};

struct FilterParams
{
    size_t centerFrequency;
    float qFactor;
    float dBAttenuation;
    FilterType filterType;
};

class IIRFilter
{
public:
    IIRFilter(FilterParams params);
    virtual ~IIRFilter();
    void run(float** ppfIn, float** ppfOut);
    
private:
    FilterParams m_filterParams;
    void calcCoefs();
    /// a-coefs for filter
    float m_aCoefs[2];
    /// b-coefs for filter
    float m_bCoefs[3];
    /// delay line
    float m_w[NCHANS][3];
    
};

IIRFilter::IIRFilter(FilterParams params)
    : m_filterParams(params)
{
    memset(m_aCoefs, 0, sizeof(m_aCoefs));
    memset(m_bCoefs, 0, sizeof(m_bCoefs));
    memset(m_w, 0, sizeof(m_w));
    printf("size of m_w: %zu", sizeof(m_w));
}

IIRFilter::~IIRFilter()
{
}

void IIRFilter::calcCoefs()
{
    // calc direct form 2 coefs
    
    // switch calculation for filter type
    
    m_aCoefs[0] = 1.0f;
    m_aCoefs[1] = 1.0f;
    m_bCoefs[0] = 1.0f;
    m_bCoefs[1] = 1.0f;
    m_bCoefs[2] = 1.0f;
}

///
/// w[n] = x[n] - a1*w[n-1] a2*w[n-2];
/// y[n] = b0*x[n] + b1*w[n-1] + b2*w[n-2];
void IIRFilter::run(float** ppfIn, float** ppfOut)
{
    for (size_t chan = 0; chan < NCHANS; chan++) {
        for (size_t samp = 0; samp < BLOCKSIZE; samp++) {
            m_w[chan][0] = ppfIn[chan][samp] - (m_aCoefs[0] * m_w[chan][1]) -  (m_aCoefs[1] * m_w[chan][2]); 
            m_w[chan][2] = m_w[chan][1];
            m_w[chan][1] = m_w[chan][0];
            ppfOut[chan][samp] = (m_bCoefs[0]*ppfIn[chan][samp]) + (m_bCoefs[1]*m_w[chan][1]) + (m_bCoefs[2]); 
        }
    }
}

static const char* getFilterType(FilterType type) 
{
    
    switch (type)
    {
        case FILTER_LOWPASS:
            return "Lowpass";
        case FILTER_HIGHPASS:
            return "Highpass";
        case FILTER_BANDPASS:
            return "Bandpass";
        case FILTER_LOWSHELF:
            return "Low-shelf";
        case FILTER_HIGHSHELF:
            return "High-shelf";
        case FILTER_BANDSTOP:
            return "Bandstop";
    }
   
    // we should never reach here
    //assert(false);
    return "";
}
int main(int argc, char** argv) 
{
    size_t fc = 500;
    float q = 1.0f;
    float gain = -3.0; // dB
    FilterType filterType = FILTER_LOWSHELF;
    
    FilterParams params = {fc, q, gain, filterType};
    printf("Filter Parameters\n");
    
    printf("Center Freq: %zu\nQ: %f\nGain: %f\nType: %s\n", 
           params.centerFrequency,
           params.qFactor,
           params.dBAttenuation,
           getFilterType(params.filterType));
    
    float** ppfIn = new float*[NCHANS];
    float** ppfOut = new float*[NCHANS];
    
    for (size_t idx = 0; idx < NCHANS; idx++) {
       ppfIn[idx] = new float[BLOCKSIZE];
       memset(ppfIn[idx], 0, sizeof(float)*sizeof(ppfIn[idx]));
       ppfOut[idx] = new float[BLOCKSIZE];
       memset(ppfOut[idx], 0, sizeof(float)*sizeof(ppfOut[idx]));
    }
    
    IIRFilter filt(params);
    
    filt.run(ppfIn, ppfOut);
    
    for (size_t idx = 0; idx < NCHANS; idx++) {
        delete[] ppfIn[idx];
        delete[] ppfOut[idx];
    }
    
    delete[] ppfIn;
    delete[] ppfOut;
    
    printf("\n");
    
    return 0;
}