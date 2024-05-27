#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "core_v_mini_mcu.h"

#define CGRA_PERIPH_START_ADDRESS (EXT_PERIPHERAL_START_ADDRESS + 0x06000)
#define CGRA_PERIPH_SIZE 0x000100
#define CGRA_PERIPH_END_ADDRESS (CGRA_PERIPH_START_ADDRESS + CGRA_PERIPH_SIZE)



const uint32_t instructions[] = {
0x101, 
0x9, 
0x1a0, 
0x220, 
0x10320, 
0x103a0, 
0xab, 
0x9ab, 
0x10ab, 
0x192b, 
0x31, 
0x89, 
0xab, 
0x9ab, 
0x10ab, 
0x192b, 
0x20010, 
0x30090, 
0x20120, 
0x302a0, 
0x118, 
0x10198, 
0xb1, 
0x28154, 
0x5, 
0x181d4, 
0x5, 
0x18254, 
0x5, 
0x202d4, 
0x5, 
0x10354, 
0x5, 
0x303d4, 
0x5, 
0x20038, 
0x20058, 
0x300d8
}; 


void operation(uint32_t *data) {
    volatile static uint32_t *cgra_cmem_ptr = (CGRA_PERIPH_START_ADDRESS);

    for (int i = 0; i < sizeof(instructions)/sizeof(uint32_t); i++) {
        cgra_cmem_ptr[i] = data[i];
    }
}


int main(int argc, char *argv[])
{
    /* write something to stdout */
    printf("hello world sw!\n");
    
    operation(instructions);
   

    return EXIT_SUCCESS;
}