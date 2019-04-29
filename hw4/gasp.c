/* Alex Htut
 * CSE_374 | HW_4
 * gasp.c
 * 05/01/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define LINE_LIMIT 500
#define PATTERN_LIMIT 100

// global variables used to
// indicate optioned flags
int ignore = 0;
int number = 0;

void check_ignore(char* star);
void print_matched_lines(int argc, char *argv[],
                         int pattern_index, char *pattern);
int count_flags(int argc, char *argv[]);

/*
 * if ignore is TRUE, change 
 * the char array, pointed by str,
 * to lowercase.
 */
void check_ignore(char* str) {
  if (ignore) {
    for (int i = 0; i < sizeof(str); i++) {
      str[i] = tolower(str[i]);
    }
  }
}


/*
 * iterates over each files, and
 * prints out the line where the pattern is found.
 * handles both ignore and number cases.
 */
void print_matched_lines(int argc, char *argv[],
                         int pattern_index, char *pattern) {
  // iterates over each file, which starts at
  // one index after the pattern_index
  for (int i = pattern_index + 1; i <= argc - 1; i++) {
    char *file_name = argv[i];
    char str[LINE_LIMIT];

    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
      fprintf(stderr, "Error while opening %s.\n", file_name);
      exit(EXIT_FAILURE);
    }

    // keeps track of the number of line
    int line_num = 1;

    // iterates over the file with while loop
    // offset the limit by 1 for null terminator
    while (fgets(str, LINE_LIMIT - 1, fp) != NULL) {
      // store the original line in org_str
      char org_str[LINE_LIMIT];
      memset(org_str, '\0', LINE_LIMIT);
      strncpy(org_str, str, sizeof(str));

      // str is changed to lowercase when ignore flag is raised.
      check_ignore(str);

      char *match_found = strstr(str, pattern);

      if (match_found != NULL) {  // NULL if no match found
        if (!number) {
          printf("%s:%s", file_name, org_str);
        } else {  // number flag is raised.
          printf("%s: l%d : %s", file_name, line_num, org_str);
        }
      }
      line_num++;
    }

    fclose(fp);
  }
}


/*
 * count the number of flags given in the cmd args.
 */
int count_flags(int argc, char *argv[]) {
  int flags_count = 0;
  for (int i = 1; i < 3; i++) {
    // strncmp returns 0 if the two strings are equal
    if (strncmp(argv[i], "-n", 2) == 0 || strncmp(argv[i], "-i", 2) == 0) {
      flags_count++;
      if (strncmp(argv[i], "-n", 2) == 0) {
        number = 1;
      } else {
        ignore = 1;
      }
    }
  }
  return flags_count;
}


/*
 * 
 */
int main(int argc, char *argv[]) {
  int flags_count = count_flags(argc, argv);
  if (argc - flags_count < 3) {
    fprintf(stderr, "Too little args! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  char pattern[PATTERN_LIMIT];

  int pattern_index = 1 + flags_count;

  // fill pattern with null char
  memset(pattern, '\0', sizeof(pattern));

  // copy 99 chars and
  // leaves 1 char for null terminator
  strncpy(pattern, argv[pattern_index], PATTERN_LIMIT - 1);

  check_ignore(pattern);

  print_matched_lines(argc, argv, pattern_index, pattern);

  return 0;
}
