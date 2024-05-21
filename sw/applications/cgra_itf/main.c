#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "core_v_mini_mcu.h"

#define CGRA_PERIPH_START_ADDRESS (EXT_PERIPHERAL_START_ADDRESS + 0x06000)
#define CGRA_PERIPH_SIZE 0x000100
#define CGRA_PERIPH_END_ADDRESS (CGRA_PERIPH_START_ADDRESS + CGRA_PERIPH_SIZE)

int main(int argc, char *argv[])
{
    /* write something to stdout */
    printf("hello world sw!\n");

    volatile static uint32_t *cgra_cmem_ptr = (CGRA_PERIPH_START_ADDRESS);
    cgra_cmem_ptr[0] = 0xDEADBEEF;

    return EXIT_SUCCESS;
}