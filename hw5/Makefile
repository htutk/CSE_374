# Alex Htut
# CSE 374 | HW5
# 05/13/2019
# Makefile: compiles trie.c, trienode.h, trienode.c
# to produce the final executable t9.

# t9 is the final target executable we want.
all: t9

# The executable
t9: trie.o trienode.o
	gcc -Wall -std=c11 -g -o t9 trie.o trienode.o
# Individual source files
trienode.o: trienode.c trienode.h
	gcc -Wall -std=c11 -g -c trienode.c

trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -g -c trie.c

# A "phony" target to remove built files and backups
clean:
	rm -f *.o t9 *~
