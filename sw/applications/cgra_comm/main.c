#include <stdio.h>
#include <stdlib.h>
#include "core_v_mini_mcu.h"
#include "x-heep.h"
#include "mmio.h"

#define CGRACOMM_PERIPH_ACC_START_ADDRESS EXT_PERIPHERAL_START_ADDRESS + 0x04000
#define CGRA_COMM_PERIPH_ACC_SIZE 0x100
#define CGRA_COMM_PERIPH_ACC_END_ADDRESS CGRA_COMM_PERIPH_ACC_START_ADDRESS + CGRA_COMM_PERIPH_ACC_SIZE


int main(int argc, char *argv[])
{
    printf("Starting test\n"); 
    volatile static uint32_t *cgra_write_call = CGRACOMM_PERIPH_ACC_START_ADDRESS;
    cgra_write_call[0] = 0xdeadbeef;
    return 0;
}

