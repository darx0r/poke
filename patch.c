#include "patch.h"
#include "ptrace.h"
#include <stdio.h>

int patch(unsigned int pid, 
          unsigned long addr, unsigned long data, unsigned long mask)
{
    int status = -1;

    status = ptrace_attach_and_wait(pid);
    if (status < 0)
    {
        printf("attach and wait failed\n");
        return -1;
    }

    unsigned long data_before = 0;
    status = ptrace_peek(pid, addr, &data_before);
    if (status < 0)
    {
        printf("peek failed\n");
        goto cleanup;
    }
    printf("[%d][0x%llx] => 0x%llx\n", pid, addr, data_before);

    if (mask == 0)
    {
        status = 0;
        goto cleanup;
    }

    const unsigned long dataq = (data_before & ~mask) | data;
    printf("[%d][0x%llx] <= 0x%llx\n", pid, addr, dataq);
    status = ptrace_poke(pid, addr, dataq);
    if (status < 0)
    {
        printf("poke failed\n");
        goto cleanup;
    }

    unsigned long data_after = 0;
    status = ptrace_peek(pid, addr, &data_after);
    if (status < 0)
    {
        printf("peek failed\n");
        goto cleanup;
    }
    printf("[%d][0x%llx] => 0x%llx\n", pid, addr, data_after);

    status = 0;

cleanup:
    ptrace_detach(pid);
    return status;
}
