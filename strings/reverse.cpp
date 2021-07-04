// Type your code here, or load an example.
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "math.h"


void reverseStringInPlace(char* in)
{
    size_t len = static_cast<size_t>(strlen(in));
    printf("strlen: %zu\n", len);
    printf("maxidx: %zu\n", len / 2);

    for (size_t idx = 0; idx < (len / 2); idx++) {
        char temp = '\n';
        temp = in[idx];
        printf("temp %c\n", temp);
        in[idx] = in[len - 1 - idx];
        in[len - 1 - idx] = temp;
    }
}

int main(int argc, char** argv)
{
    // reverse string in place
    char inString[] = "abcdefg";
    printf("input string: %s\n", inString);
    reverseStringInPlace(inString);
    printf("reversed string: %s\n", inString);
}