#include "ptrace.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

void alarm_handler(int signum) {}

int ptrace_attach_and_wait(unsigned int pid)
{
    const long status = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    if (status < 0)
    {
        return -1;
    }

    const void* prev_handler = signal(SIGALRM, alarm_handler);
    if (prev_handler != 0)
    {
        ptrace_detach(pid);
        return -1;
    }

    static const unsigned int ATTACH_TIMEOUT = 10;
    alarm(ATTACH_TIMEOUT);
    static int* NO_STATUS = NULL;
    const unsigned int attached_pid = waitpid(pid, NO_STATUS, WSTOPPED);
    alarm(0);

    if (attached_pid != pid)
    {
        ptrace_detach(pid);
        return -1;
    }

    return 0;
}

int ptrace_detach(unsigned int pid)
{
    const long status = ptrace(PTRACE_DETACH, pid, NULL, NULL);
    if (status < 0)
    {
        return -1;
    }

    return 0;
}

int ptrace_peek(unsigned int pid, unsigned long addr, unsigned long* out)
{
    errno = 0;
    const long data = ptrace(PTRACE_PEEKDATA, pid, addr, NULL);
    if (errno != 0 && data < 0)
    {
        return -1;
    }

    *out = data;
    return 0;
}

int ptrace_poke(unsigned int pid, unsigned long addr, unsigned long data)
{
    const long status = ptrace(PTRACE_POKEDATA, pid, addr, data);
    if (status < 0)
    {
        return -1;
    }

    return 0;
}

