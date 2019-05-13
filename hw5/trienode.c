// Alex Htut
// CSE 374 | HW 5
// trienode.c 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trienode.h"

TrieNode* makeNode() {
  TrieNode *t = (TrieNode*) malloc(sizeof(TrieNode));
  for (int i = 0; i < NUM_NODES; i++) {
    t->next[i] = NULL;
  }
  t->word[0] = (char) 0;
  return t;
}


void modifyWord(TrieNode *t, char *str) {
  char *wordPtr = t->word;
  strncpy(wordPtr, str, strlen(str));
}

void freeTrie_private(TrieNode *t) {
  if (t) {
    int nullChecker = 1;  // assume every node is null
    for (int i = 0; i < NUM_NODES; i++) {
      if (t->next[i]) {  // not null
        nullChecker = 0;
      }
    }

    // every single node of next is null
    if (nullChecker) {
      //printf("free something\n");
      free(t);
    } else {
      TrieNode *ptr;
      for (int i = 0; i < NUM_NODES; i++) {
        //printf("i is %d", i);
        //printf("\n");
        ptr = t->next[i];
        freeTrie_private(ptr);
      }
      //free(t->word);
      free(t);
    }
  } else {
    //printf("I am null.\n");
  }
}


#define fp freeTrie_private
void freeTrie(TrieNode *t) {
  fp(t);
}
#undef fp

void printTrie(TrieNode *t) {
  char *wordPtr = t->word;
  if (wordPtr != NULL) {
    printf("%s\n", wordPtr);
  }
}