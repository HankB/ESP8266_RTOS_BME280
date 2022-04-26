#include <stdio.h>

#include "local.h"

/*
gcc -o fprintf -Wall -DHOST_TEST fprintf.c 
*/

const char *my_snfprintf(char *buf, int buf_len, float val)
{
    int i_val = (int)((val)*100+0.5); //calculate rounded int value x 100
    int whole = i_val/100;
    int frac = i_val%100;    
    snprintf(buf, buf_len,  "%d.%02d", whole, frac);
    return buf;
}

#if defined HOST_TEST
#include <string.h>

int main( int argc, char** argv) 
{
    float val = 1234.56;
    const int len=100;
    char buf[len];
    char snprintf_buf[len];

    for( val=0.0; val<1000.0; val += 0.01)
    {
        snprintf(snprintf_buf, len, "%.02f", val);
        my_snfprintf(buf, len, val);
        if(strcmp(snprintf_buf, buf))
            printf("%f, %.02f, %s, %s\n", val, val, buf, snprintf_buf);
    }
}
#endif