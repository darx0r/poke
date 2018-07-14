#pragma once

int ptrace_attach_and_wait(unsigned int pid);
int ptrace_detach(unsigned pid);
int ptrace_peek(unsigned pid, unsigned long addr, unsigned long* out);
int ptrace_poke(unsigned pid, unsigned long addr, unsigned long data);

