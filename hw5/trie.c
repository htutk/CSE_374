// Alex Htut
// CSE 374 | HW 5
// 05/13/2019
// trie.c
// main file to implement the executable t9.
// t9 takes in a single filename argument which
// includes a 'word' dictionary, builds a trie-like
// structure to make that dictionary, and implements
// an interactive program with user.
// After the dicitonary is processed, the user may enter
// numbe-sequence(s) to retrieve corresponding word(s) that
// are defined in the dictionary.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trienode.h"

#define MAX_CHAR 100
#define OFFSET_DIGIT 50  // ascii of '2' = 50

// function declarations
void addWord(TrieNode *t, char *series, char *word);
void startInteractive(TrieNode *root);
int allNumbers(char *seq);
char charToNum(char c);
char* wordToNum(char *word);
TrieNode* processWord(TrieNode *root, char *seq, int hash);

// processes each line in the file and adds the word to the
// trie dictionary.
// then starts an interactive program where the user may give
// a number-sequence to retrieve a defined word.
// frees the trie dictionary after the interactive program terminates.
// exits with success if the user 'exits' the program successfully.
// exits with failure if the args count is not 1.
// exits with failure if the given file cannot be open.
// exits with failure if malloc for the root node fails.
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "%s takes a single filename arg.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Error loading %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    TrieNode *root = makeNode();
    if (root == NULL) {
        exit(EXIT_FAILURE);
    }

    char str[MAX_CHAR];
    while (fgets(str, MAX_CHAR, f) != NULL) {
        // copy the actual word to the trie dictionary.
        char *word = (char *) malloc(strlen(str) * sizeof(char));
        strncpy(word, str, strlen(str));
        word = strtok(word, "\n");

        char *series = wordToNum(word);
        if (series == NULL) {
            fprintf(stderr, "Error reading line: invalid chars.\n");
            continue;
        }
        addWord(root, series, word);
        free(series);
    }
    startInteractive(root);
    fclose(f);  // close the opened file.
    freeTrie(root);
    return EXIT_SUCCESS;
}

// initializes the interactive program after the dictionary is processed.
// given a number-sequence by the user, the program finds the sequence in
// the trie dictionary. If found, prints the word; if not, prints a message.
// '#' is a special character; given a hashtag alone, it will continue the
// search on the previous sequence. Given with a sequence, it will find the
// next word of that sequence (but the sequence itself).
// multiple hashtags are allowed.
// terminates the program if the user enters 'exit'.
void startInteractive(TrieNode *root) {
    char input[MAX_CHAR] = "";
    char *seq = input;
    printf("Enter \"exit\" to quit.\n");
    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
    scanf("%s", input);
    if (feof(stdin)) {
      printf("\n");
      return;
    }

    TrieNode *current = root;

    while (strncmp(seq, "exit", 4)) {
        if (allNumbers(seq)) {
            int firstChar = (int) seq[0];
            int hash = 1;
            if (!(firstChar < 50 || firstChar > 57)) {
                current = processWord(root, seq, !hash);
            } else if (firstChar == 35) {  // 35 is hash tag
                current = processWord(current, seq, hash);
            }
            if (current == NULL) {
                current = root;
            }
            printf("Enter Key Sequence (or \"#\" for next word):\n> ");
        } else {
            printf("Enter a sequence of numbers (2-9):\n> ");
        }
        scanf("%s", input);
        if (feof(stdin)) {
          printf("\n");
          return;
        }
    }
}

// given a seq, finds the word in the root dictionary and
// prints out the word. For hashtag-included sequence, the search
// will begin on the 'current' node, not the overall-parent node.
// some messages are printed out only if hashtag is included, which
// is checked by 'hash' flag.
TrieNode* processWord(TrieNode *root, char *seq, int hash) {
    TrieNode *current = root;
    for (int i = 0; i < strlen(seq); i++) {
        int ascii = (int) seq[i];
        int index;
        if (ascii == 35) {
            index = 8;
        } else {
            index = ascii - OFFSET_DIGIT;
        }
        if (current == NULL) {
            printf("Not found in current directory.\n");
            return NULL;
        }
        if (current->next[index] != NULL) {
            current = current->next[index];
        } else if (hash) {  // this error message is for #-included seq.
            printf("There are no more T9onyms\n");
            return NULL;
        } else {
            printf("Not found in current directory.\n");
            return NULL;
        }
    }
    if (current != NULL) {
        printTrie(current);
    }
    return current;
}

// checks if the given seq is all valid numbers (2-9 or #).
// returns 1 if true, 0 if not.
int allNumbers(char *seq) {
    for (int i = 0; i < strlen(seq); i++) {
        int ascii = (int) seq[i];
        if (ascii == 35) {  // pound key
            continue;
        }

        if (ascii < 50 || ascii > 57) {
            return 0;
        }
    }
    return 1;
}

// add word to the root dictionary by iterating through
// series sequence.
// given '87' for the word 'up', it will create a node at
// index 8 first (if NULL), move to that next node, create
// a node at index 7 (if NULL), then writes the word.
// if the word already exits, it will endlessly search for
// the '#" child, where the word field is NULL, and writes
// the word where the first NULL (for word) is found.
void addWord(TrieNode *root, char *series, char *word) {
    // ascii 50-57 -> 2-9
    TrieNode *rootPtr = root;
    for (int i = 0; i < strlen(series); i++) {
        int index = ((int) series[i]) - OFFSET_DIGIT;
        if (!rootPtr->next[index]) {
            rootPtr->next[index] = makeNode();
            if (rootPtr->next[index] == NULL) {
                return;
            }
        }
        rootPtr = rootPtr->next[index];
    }

    while (rootPtr->word != NULL) {
        if (!rootPtr->next[NUM_NODES - 1]) {  // last index is pound key
            rootPtr->next[NUM_NODES - 1] = makeNode();
            if (rootPtr->next[NUM_NODES - 1] == NULL) {
                return;
            }
        }
        rootPtr = rootPtr->next[NUM_NODES - 1];
    }
    modifyWord(rootPtr, word);
}

// translates a word to its corresponding Trie-number string.
// ex. "jello" -> "53556".
// returns Null if a non-letter is detected in a given string.
char* wordToNum(char *word) {
    // offset the size by 1 for null terminator from strncpy.
    char *result = (char *) malloc(strlen(word) * sizeof(char) + 1);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < strlen(word) + 1; i++) {
        result[i] = '\0';  // initializes each space, otherwise valgrind err
    }
    char *ptr = result;
    for (int i = 0; i < strlen(word); i++) {
        *ptr = charToNum(word[i]);
        if (*ptr == '1') {
            printf("Word is %s", word);
            printf("result is %s.\n", result);
            free(result);
            return NULL;
        }
        ptr++;
    }
    return result;
}

// returns a corresponding Trie-digit of char c.
// returns '1' if c is not a letter.
char charToNum(char c) {
    int charNum = (int) c;
    int decryptedNum = charNum;
    // to be a char (A-Z and a-z)
    // charNum has to be 65-90 (A-Z)
    // or 97-122) (a-z)
    if (charNum >= 65 && charNum <= 90) {
        decryptedNum = charNum - 65;
    } else if (charNum >= 97 && charNum <= 122) {
        decryptedNum = charNum - 97;
    } else {
        return '1';
    }

    char encrypted[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5',
    '5', '5', '6', '6', '6', '7', '7', '7', '7', '8', '8',
    '8', '9', '9', '9', '9'};
    return encrypted[decryptedNum];
}

