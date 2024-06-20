#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "core_v_mini_mcu.h"

#define CGRA_PERIPH_START_ADDRESS (EXT_PERIPHERAL_START_ADDRESS + 0x06000)
#define CGRA_PERIPH_SIZE 0x000100
#define CGRA_PERIPH_END_ADDRESS (CGRA_PERIPH_START_ADDRESS + CGRA_PERIPH_SIZE)



const uint32_t instructions[] = {
0x81,
0x9,
0x1e3,
0x36ab,
0x30020,
0x300a0,
0x31,
0x89,
0x10ab,
0x10020,
0x10120,
0xb1,
0x109,
0xd0090,
0xd0ab,
0x20ab,
0x20020,
0x201a0,
0x131,
0x189,
0x240ab,
0xe0ab,
0xe0110,
0x240020,
0x240220,
0x1b1,
0x209,
0x190690,
0x190710,
0x191ab,
0x1a0020,
0x231,
0x289,
0x251210,
0x250c90,
0x2512b,
0xd18,
0x2b1,
0x54,
0x5,
0xd4,
0xd,
0x154,
0x5,
0x1d4,
0xd,
0x254,
0x15,
0xb8,
}; 


#define N_LIVEOUTS 1
const uint32_t liveout_instr[] = {
    0x59
};



void operation(uint32_t *data, uint32_t *extractint, uint8_t n_liveouts) {
    volatile static uint32_t *cgra_cmem_ptr = (CGRA_PERIPH_START_ADDRESS);

    // Config and start execution instructions
    for (int i = 0; i < sizeof(instructions)/sizeof(uint32_t); i++) {
        cgra_cmem_ptr[i] = data[i];
    }

    int a; 
    // Retrieve liveout instructions
    for (int i = 0; i < n_liveouts; i++) {
        cgra_cmem_ptr[i] = extractint[i]; // send the instruction to the cgra
        a = cgra_cmem_ptr[i]; // read the result from the cgra
    }
}



int main(int argc, char *argv[])
{
    // do stuff here
    operation(instructions, liveout_instr, N_LIVEOUTS);
    return EXIT_SUCCESS;
}