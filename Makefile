
poke: poke.c patch.c ptrace.c
	gcc $+ -o $@

all: poke 

clean:
	rm -f poke
