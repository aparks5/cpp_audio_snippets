#include "stdio.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"

#define MAX_LEN (128)
#define RARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
// Write a program that prints the numbers from 1 to 100.
// But for multiples of three print “Fizz” instead of the number 
// and for the multiples of five print “Buzz”. 
int main(int argc, char** argv)
{
    size_t frameLen = 2;
    size_t nChans = 2;
    size_t nSamps = 4;
    int arr[8] = {0,1,0,1,0,1,0,1};

    printf("input\n");
    for (size_t chan = 0; chan < nChans; chan++) {
        for (size_t samp = 0; samp < nSamps; samp++) {
            printf("%d", arr[samp+(frameLen*chan)]);
        }
    }

    printf("\noutput pre deinterleaved\n");
    int out[8];
    memset(out, 0, sizeof(out));
    for (size_t chan = 0; chan < nChans; chan++) {
        for (size_t samp = 0; samp < nSamps; samp++) {
            printf("%d", out[samp+(frameLen*chan)]);
        }
    }


    printf("\ndeinterleaved\n");

    for (size_t chan = 0; chan < nChans; chan++) {
        for (size_t samp = 0; samp < nSamps; samp++) {
            printf("%d", arr[(nChans*samp)+chan]);
       }
    }


    printf("\nstored and deinterleaved\n");
    for (size_t chan = 0; chan < nChans; chan++) {
        for (size_t samp = 0; samp < nSamps; samp++) {
            out[samp+(nSamps*chan)] = arr[(nChans*samp)+chan]; 
            printf("%d", out[samp+(nSamps*chan)]);
       }
    }
 


}

