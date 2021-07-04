#include "stddef.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define BUFLEN (16)
#define INLEN (4)

class CircBuff
{
public:
    CircBuff(size_t nChans, size_t bufLen);
    virtual ~CircBuff();

    void write(float* fData);
    float readNext();
    void reset();
    size_t getLen() { return m_bufLen; }

private:
    float** m_ppfCircBuff;
    size_t m_readIdx;
    size_t m_writeIdx;
    size_t m_numChans;
    size_t m_bufLen;
};

CircBuff::CircBuff(size_t nChans, size_t bufLen)
    : m_ppfCircBuff(NULL)
    , m_readIdx(0)
    , m_writeIdx(0)
    , m_numChans(nChans)
    , m_bufLen(bufLen)
{
    m_ppfCircBuff = new float*[nChans];

    for (size_t idx = 0; idx < m_numChans; idx++) {
        m_ppfCircBuff[idx] = new float[bufLen];
        memset(m_ppfCircBuff[idx], 0, sizeof(m_ppfCircBuff[idx]));
    } 

}

CircBuff::~CircBuff()
{
    for (size_t idx = 0; idx < m_numChans; idx++) {
        delete[] m_ppfCircBuff[idx];
        m_ppfCircBuff[idx] = NULL;
    }

    delete[] m_ppfCircBuff;
    m_ppfCircBuff = NULL;
}

void CircBuff::reset()
{
    for (size_t idx = 0; idx < m_numChans; idx++) {
        memset(m_ppfCircBuff[idx], 0, sizeof(m_ppfCircBuff[idx]));
    } 

    m_readIdx = 0;
    m_writeIdx = 0;
}

void CircBuff::write(float* fData)
{
    m_writeIdx = (m_writeIdx + 1) % m_bufLen;
    for (size_t idx = 0; idx < m_numChans; idx++) {
        m_ppfCircBuff[idx][m_writeIdx] = fData[idx];
    }
}

float CircBuff::readNext() 
{

    m_readIdx = (m_writeIdx + 1) % m_bufLen;
    m_writeIdx = (m_writeIdx + 1) % m_bufLen;
    float result = m_ppfCircBuff[0][m_readIdx];
    return result;
}

int main(int argc, char** argv)
{

    CircBuff circBuff(1, BUFLEN);

    float inBuff[INLEN];

    printf("input buffer contents\n");
    for (size_t idx = 0; idx < INLEN; idx++) {
        inBuff[idx] = 1.0f;
        printf("%f\n", inBuff[idx]);
    }


    printf("circ buffer contents\n");

    circBuff.write(inBuff);

    for (size_t idx = 0; idx < circBuff.getLen(); idx++) {
        printf("%f\n ", circBuff.readNext());
    }

    return 0;
}