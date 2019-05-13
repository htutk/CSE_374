// Alex Htut
// CSE 374 | HW 5
// trie.c -
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trienode.h"

#define MAX_CHAR 100
#define OFFSET_DIGIT 50

char charToNum (char c);
char* wordToNum (char *word);
void addWord(TrieNode *t, char *series, char *word);
void startInteractive(TrieNode *root);
int allNumbers(char *seq);
int processWord(TrieNode *root, char *seq);

int main (int argc, char **argv) {
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

    char str[MAX_CHAR];

    while (fgets(str, MAX_CHAR, f) != NULL) {
        //printf("Word is %s", str);
        char *strPtr = str;
        char *encryptedWord = wordToNum(str);
        printf("Encrypted is %s.\n", encryptedWord);
        printf("strPtr is %s.\n", strPtr);

        addWord(root, encryptedWord, strPtr);

        free(encryptedWord);
    }

    startInteractive(root);

    fclose(f);
    freeTrie(root);

    return EXIT_SUCCESS;
}

void startInteractive(TrieNode *root) {
    char str[MAX_CHAR] = "";
    char *seq = str;
    printf("Enter \"exit\" to quit.\n");
    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
    scanf("%s", seq);

    while (strncmp(seq, "exit", 4)) {
        if (allNumbers(seq)) {
            if (processWord(root, seq)) {
                printf("Not found in current directory.\n");
            }
            printf("Enter Key Sequence (or \"#\" for next word):\n> ");
        } else {
            printf("Enter a sequence of numbers (2-9):\n> ");
        }
        //printf("Strlen is %ld.\n", strlen(seq));
        
        scanf("%s", seq);
    }

}

int processWord(TrieNode *root, char *seq) {
    
    TrieNode *current = root;
    for (int i = 0; i < strlen(seq); i++) {
        int ascii = (int) seq[i];
        int index;
        if (ascii == 35) {
            index = 8;
        } else {
            index = ascii - OFFSET_DIGIT;
        }
        current = current->next[index];
        if (current == NULL) {
            return 1;
        }
        printf("index: %d\n", index);
    }
    printf("%s", current->word);
    return 0;
}

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

void addWord(TrieNode *root, char *series, char *word) {
    // ascii 50-57 -> 2-9
    TrieNode *rootPtr = root;
    for (int i = 0; i < strlen(series); i++) {
        int index = ((int) series[i]) - OFFSET_DIGIT;
        if (!rootPtr->next[index]) {
            rootPtr->next[index] = makeNode();
        }
        rootPtr = rootPtr->next[index];
        printf("index of addWord is %d.\n", index);
    }

    while (rootPtr->word != NULL) {
        if(!rootPtr->next[NUM_NODES - 1]) {  // last index is pound key
            rootPtr->next[NUM_NODES - 1] = makeNode();
        }
        rootPtr = rootPtr->next[NUM_NODES - 1];
        printf("Pound made!\n");
    }

    modifyWord(rootPtr, word);
    //printf("Series is %s.\n", series);
    printTrie(rootPtr);
}

/*
 * Translates a word to its corresponding Trie-number string.
 * Ex. "jello" -> "53556"
 * Returns Null if a non-letter is detected in a given string.
 */
char* wordToNum(char *word) {
    char *result = (char *) malloc(strlen(word) * sizeof(word));
    char *ptr = result;

    for (int i = 0; i < strlen(word) - 1; i++) {  //offset by 1 for null term
        *ptr = charToNum(word[i]);
        if (*ptr == '1') {
            return NULL;
        }
        ptr++;
    }

    return result;
}

/*
 * Returns a corresponding Trie-digit of char c.
 * Returns '1' if c is not a letter.
 */ 
char charToNum (char c) {
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