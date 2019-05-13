# CSE 374 Makefile exampmle for the talk/speak/shout program.
# Version 1: Basic

# When we just run "make", what gets built? This is a "phony" target
# that just tells make what other targets to build.
all: trie9

# The executable
trie9: trie.o trienode.o
	gcc -Wall -std=c11 -g -o trie9 trie.o trienode.o
# Individual source files
trienode.o: trienode.c trienode.h
	gcc -Wall -std=c11 -g -c trienode.c

trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -g -c trie.c

# A "phony" target to remove built files and backups
clean:
	rm -f *.o trie *~
