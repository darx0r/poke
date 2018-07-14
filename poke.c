#include "patch.h"
#include <stdio.h>
#include <stdlib.h>

enum 
{
    ARGS_PROGRAM,
    ARGS_PID,
    ARGS_SIZE,
    ARGS_ADDR,
    ARGS_DATA,
    NUM_OF_ARGS
} ARGS;

int main(int argc, char* argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        printf("%s <pid> [0|b|h|d|g] <addr> <val>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const unsigned int pid = atoi(argv[ARGS_PID]);
    const unsigned char size = argv[ARGS_SIZE][0];
    const unsigned long addr = strtol(argv[ARGS_ADDR], NULL, 16);
    unsigned long data = strtol(argv[ARGS_DATA], NULL, 16);

    unsigned long mask = 0;
    switch (size)
    {
        case '0':
            mask = 0;
            break;
        case 'b':
            mask = 0xFF;
            break;
        case 'h':
            mask = 0xFFFF;
            break;
        case 'd':
            mask = 0xFFFFFFFF;
            break;
        case 'g':
            mask = 0xFFFFFFFFFFFFFFFF;
            break;
        default:
            printf("bad size modifier\n");
            return EXIT_FAILURE;
    }

    data &= mask;
    if (patch(pid, addr, data, mask) < 0)
    {
        printf("patch failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

