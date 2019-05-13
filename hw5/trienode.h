// Alex Htut
// CSE 374 | HW 5
// trienode.h

#ifndef NUM_NODES
#define NUM_NODES 9
#endif

// A single TrieNode that stores the number/'#' as num.
// The node will also have a string if its next is NULL or '#'
typedef struct TrieNode{
  // next[0] - next[7] for 2 - 9
  // next[8] for pound key
  struct TrieNode* next[NUM_NODES];
  char word[];
} TrieNode;

TrieNode* makeNode();

void modifyWord(TrieNode *t, char *str);

// print out the word in the trie node if exits
void printTrie(TrieNode *t);

// 
void freeTrie(TrieNode *t);
