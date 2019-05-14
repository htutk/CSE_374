// Alex Htut
// CSE 374 | HW 5
// 05/13/2019
// trienode.h
// header file for TrieNode class

#ifndef NUM_NODES
#define NUM_NODES 9

// A single TrieNode that stores char* to store a word,
// and an array of next that has 9 TrieNodes, which are intialized to NULL.
typedef struct TrieNode {
  // next[0] - next[7] for 2 - 9
  // next[8] for pound key
  struct TrieNode* next[NUM_NODES];
  char *word;
} TrieNode;

TrieNode* makeNode();

// modify the word parameter in TrieNode t.
void modifyWord(TrieNode *t, char *word);

// print out the word in the trie node if exits
void printTrie(TrieNode *t);

// recurisvely free the TrieNode t and all of its children.
void freeTrie(TrieNode *t);

#endif
