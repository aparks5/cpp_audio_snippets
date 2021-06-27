#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"

#define MAX_LEN (128)
#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))

/// This code interleaves and de-interleaves arrays of ints and stores them in a single array.
/// The trick to deinterleaving and interleaving lies entirely in how you think about the indexing.
/// Interleaved samples are chunked into channel-groups, while de-interleaved samples are chunked into sample-groups.
/// In interleaved buffers, each channel-group has a number of samples equal to the number of channels, with each group containing only one sample per channel. 
/// In deinterleaved buffers, each sample-group contains a number of samples equal to the size of the buffer, with each group representing one channel's buffer contents.

// E.g. a 128 sample buffer interleaved for 2 channels would need
// 256 samples. The interleaved buffer is 128 groups of 2. The de-interleaved buffer needs 256 samples, but is arranged like 2 groups of 128.
//
// INTERLEAVED:
// | L R | L R | L R | L R | etc.
// |--^--|
// |group|group|group|
//
//  DE-INTERLEAVED:
/// | L L L L etc. | R R R R etc. |
//  |-------^------|
//  |     group    |    group     |
//
// This means that if we go "looking for stuff" inside buffers, we need to look at the logical groupings within the buffers and advance by "sub-indexing".
//
// In other words, if you have a single contiguous array that is grouped somehow logically within it, you need to index by the following:
//
// x[groupSizeOffset + subIndexOfInterest]
//
// The group size of an interleaved buffer is going to be the number of channels. The offset is calculated by multiplying the group size by the group index.
// In interleaved audio, we group by clusters of channel data for one sample. So the group index is the sample index of the buffer. The sub-indices within an individual group are indicated by each channel.
//
// In a de-interleaved buffer, the group size is the number of samples. The offset is also calculated by multiplying the group size by the group index. However, in this case
// our group size is the total number of samples, and the group index is the channel index. We sub-index into each de-interleaved group by looking at a particular sample.
//
// The beauty of this is that we can de-interleave just as we would de-interleave, but just swap the assignment:
// deinterleaved[(totalSamples*channel)+sample] = interleaved[(totalChannels*sample)+channel]
// interleaved[(totalChannels*sample)+channel] = deinterleaved[(totalSamples*channel)+sample]
//
// Another way of thinking about this is if audio, or any data buffer, is interleaved, it means that the data is arranged in such a way
// that it is grouped logically by clusters of samples sub-indexed by channel, while de-interleaved buffers are grouped logically by clusters of samples sub-indexed by sample index.
//
// In summary, the size of logical groups within an array and sub-indexing an element of interest is what makes a buffer de-interleaved or interleaved.
//
void testDeinterleave()
{
    size_t frameLen = 2;
    size_t nChans = 2;
    size_t nSamps = 4;
    int arr[8] = {0,1,0,1,0,1,0,1};

    printf("\n-----------------\n");
    printf("interleaved input\n");
    
    for (size_t chan = 0; chan < nChans; chan++) {
        for (size_t samp = 0; samp < nSamps; samp++) {
            printf("%d", arr[samp+(frameLen*chan)]);
        }
    }
    
    printf("\n");
    printf("deinterleaved output \n");

    printf("\nstored and deinterleaved\n");
    for (size_t chan = 0; chan < nChans; chan++) {
        for (size_t samp = 0; samp < nSamps; samp++) {
            out[samp+(nSamps*chan)] = arr[(nChans*samp)+chan];
            printf("%d", out[samp+(nSamps*chan)]);
       }
    }

}

void testInterleave()
{
    size_t nchans = 4;
    size_t sampsPerChan = 3;

    int input[12] = {1,1,1,2,2,2,3,3,3,4,4,4};
    // should output 1,2,3,4,1,2,3,4,1,2,3,4 when interleaved
    int output[12];
    memset(output, 0, sizeof(output));
    
    printf("\n-----------------\n");
    printf("deinterleaved input\n");
    for (size_t chan = 0; chan < nchans; chan++)
        for (size_t samp = 0; samp < sampsPerChan; samp++) {
            printf("%d", input[(chan*sampsPerChan) + samp]);
            output[(nchans*samp) + chan] = input[(sampsPerChan * chan) + samp];
    }
    printf("\n");
    printf("interleaved output:\n");
    for (size_t idx = 0; idx < 12; idx++) {
        printf("%d", output[idx]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    testDeinterleave();
    testInterleave();
    return 0;
}
