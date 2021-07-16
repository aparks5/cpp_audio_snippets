#include "stdio.h"


// linear interpolation, line between two points:
// y - y0 / x - x0 = y1 -y0 / x1 - x0
// we can for y by multiplying through 
float interpolateLinear(float x1, float x2, float y1, float y2, float x)
{
    return y1 + ((x - x1) / (x2 - x1)) * (y2 -y1);
}

int main()
{
    // fractional delay

    float yn = buff[m_nReadIndex];

    // if delay < 1 samp, set yn = xn

    // read location behind yn
    if (nReadIndex_1) = m_nRead_index - 1;

    // wrap nReadIndex_1

    if (nReadIndex_1 < 0) {
        nReadIndex = m_nBufferSize - 1;
    }

    // get y(n-1), needed for interpolation formula

    float yn_1 = buff[nReadIndex_1];

    /// interpolate (0,yn) and (1,yn_1) by the amount fracDelay
    float fFracDelay = m_fDelayInSamples - (int)m_fDelayInSamples;

    // linear interpolation: x1,x2,y1,y2,x
    float fInterp = interpolateLinear(0, 1, yn, yn_1, fFracDelay);

    float yn = fInterp;
    // you will hear a repetitive click, need wrap across buffer[0] to buffer[size-1]

}
