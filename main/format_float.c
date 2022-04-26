#include <stdio.h>

/*
Testing on host OS
gcc -DTEST_ON_HOST -o format_float -Wall main/format_float.c 
./format_float

hbarta@olive:~/Programming/ESP8266/ESP8266_RTOS_BME280$ ./format_float
 0, 3.0
 1, 3.1
 2, 3.14
 3, 3.142
 4, 3.1416
 5, 3.14159
 6, 3.141593
 7, 3.1415927
 8, 3.14159274
 9, 3.141592736
10, 3.199655024
11, 3.172141680
12, 3.-102991720
13, 3.186355152
14, 3.39142920
15, 3.-216706976
16, 3.265474976
17, 3.222205040
18, 3.-210494400
19, 3.-280535488

NB: Results are correct for 0 > n > 10 which fits the domain
    desired for this project.
*/

/**
 * my_float_print()
 * buf - place to store formatted result\
 * buflen - length of buf
 * val - value to be formatted
 * dec - number of desired decimal places [1-9]
 **/
const char *my_float_print(char* buf, int buflen, float val, int dec)
{
    int multiplier=1;   // to convert fractional portion to int
    float bias=0.5;     // to use to round properly
    int loop_count=dec; // to adjust bias, multiplier for # of fractional digits

    while(loop_count-->0)
    {
        multiplier *= 10;
        bias /= 10;
    }
    snprintf(buf, buflen, "%d.%d", (int)(val),
                (int)(( (val-(int)(val))+bias) *multiplier));
    return buf;
}

#ifdef TEST_ON_HOST
int main(int argc, char **argv)
{
    const int len=100;
    char buf[len];
    float val=3.14159265358979323846;

    for( int i=0; i<20; i++)
    {
        printf("%2d, %s\n", i,  my_float_print(buf, len, val, i));
    }

    val = 1.9;

    for( int i=0; i<40; i++)
    {
        printf("%2d, %s, %f\n", i,  my_float_print(buf, len, val, 2), val);
        val += 0.1;
    }

}
#endif