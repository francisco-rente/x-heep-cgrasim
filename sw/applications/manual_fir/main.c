#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "core_v_mini_mcu.h"

#define CGRA_PERIPH_START_ADDRESS (EXT_PERIPHERAL_START_ADDRESS + 0x06000)
#define CGRA_PERIPH_SIZE 0x000100
#define CGRA_PERIPH_END_ADDRESS (CGRA_PERIPH_START_ADDRESS + CGRA_PERIPH_SIZE)


char array1[64] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};
char arra2[64];


char coeffs[3] = {1, 2, 3};

void kernel(char *array1, char *array2, char *coeffs, int size)
{
    char samples[3] = {0, 0, 0};
    
    for (int i = 0; i < size; i++)
    {
        samples[2] = samples[1];
        samples[1] = samples[0];
        samples[0] = array1[i];
        
        array2[i] = coeffs[0] * samples[0] + coeffs[1] * samples[1] + coeffs[2] * samples[2];
    }
}



int main(int argc, char *argv[])
{
    // do stuff here
    kernel(array1, arra2, coeffs, 64);
    return EXIT_SUCCESS;
}
