# poke
Everynody wants a simple, yet powerful, cheat-engine like capability on linux!
Poke is a command-line tool with gdb-like syntax for live process memory patching based on ptrace.

## usage
poke <pid> [0|b|h|d|g] \<addr\> \<val\>
  * pid - process id
  * 0 - just read
  * b|h|d|g - gdb-like write size modifer
  * addr - address (hex)
  * val - value (hex)

Let the cheat begin!
