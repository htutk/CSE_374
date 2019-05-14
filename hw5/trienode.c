// Alex Htut
// CSE 374 | HW 5
// 05/13/2019
// trienode.c
// main class to implement TrieNode class.
// contains methods such as makeNode to make new nodes,
// printTrie to print out the word, etc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trienode.h"

// return a single 'empty' TrieNode if malloc succeeds.
// all the next nodes and the word pointer are set to NULL initially.
TrieNode* makeNode() {
  TrieNode *t = (TrieNode*) malloc(sizeof(TrieNode));
  if (t == NULL) {
    return NULL;
  }
  for (int i = 0; i < NUM_NODES; i++) {
    t->next[i] = NULL;
  }
  t->word = NULL;
  return t;
}

// sets the word field in TrieNode t to 'word' parameter.
void modifyWord(TrieNode *t, char *word) {
  t->word = word;
}

// private method to recursively free the node t.
// free t's word, its children (and their children), and the node itself.
void freeTrie_private(TrieNode *t) {
  if (t) {
    TrieNode *ptr;
    for (int i = 0; i < NUM_NODES; i++) {
      ptr = t->next[i];
      freeTrie_private(ptr);
    }
    if (t->word != NULL) {
      free(t->word);
    }
    free(t);
  }
}

// public method to free the node t.
#define fp freeTrie_private
void freeTrie(TrieNode *t) {
  fp(t);
}
#undef fp

// prints out the word in TrieNode t if not NULL.
// if NULL, conclude that the word has not been found.
void printTrie(TrieNode *t) {
  if (t->word != NULL) {
    printf("'%s'\n", t->word);
  } else {
    printf("Not found in current dictionary.\n");
  }
}
