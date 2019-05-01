/* Alex Htut
 * CSE_374 | HW_4
 * gasp.c
 * 05/01/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// MAX charallowed in line and pattern
#define LINE_LIMIT 500
#define PATTERN_LIMIT 100

// global variables used to
// indicate optioned flags
int ignore = 0;
int number = 0;

// function declarations
void check_ignore(char* star);
void print_matched_lines(int argc, char *argv[],
                         int pattern_index, char *pattern);
int count_flags(int argc, char *argv[]);
void check_args(int argc, int flag_count);

/*
 * If ignore is TRUE, change 
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
 * Iterates over each files given in FILE in argv[], and
 * prints out the line where the pattern is found.
 * FILE starts at pattern_index + 1.
 * Handles both ignore and number cases.
 */
void print_matched_lines(int argc, char *argv[],
                         int pattern_index, char *pattern) {
  // iterates over each file, which starts at
  // one index after the pattern_index
  for (int i = pattern_index + 1; i <= argc - 1; i++) {
    char *file_name = argv[i];

    char str[LINE_LIMIT];

    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {  // note that fopen is able to open folder
      fprintf(stderr, "Error while opening %s.\n", file_name);
      continue;
    }

    // keeps track of the number of line
    int line_num = 1;

    // iterates over the file with while loop
    // offset the limit by 1 for null terminator
    while (fgets(str, LINE_LIMIT - 1, fp) != NULL) {
      // store the original line in org_str
      char org_str[LINE_LIMIT];
      char *org_str_ptr = org_str;
      
      if (ignore) {
        strncpy(org_str, str, sizeof(str));  // makes a copy only if -i is set.
      } else {
        org_str_ptr = str;
      }

      // str is changed to lowercase when ignore flag is raised.
      check_ignore(str);

      char *match_found = strstr(str, pattern);

      if (match_found != NULL) {  // NULL if no match found
        if (!number) {
          printf("%s:%s", file_name, org_str_ptr);
        } else {  // number flag is raised.
          printf("%s:%d:%s", file_name, line_num, org_str_ptr);
        }
      }
      line_num++;
    }

    fclose(fp);
  }
}


/*
 * Counts the number of flags given in the cmd args, and returns it.
 * Assumes that the flags exist only in 2rd and/or 3rd args.
 * Sets global variables number, ignore accordingly.
 */
int count_flags(int argc, char *argv[]) {
  int flags_count = 0;
  for (int i = 1; i < 3; i++) {
    // strncmp returns 0 if the two strings are equal
    if (strncmp(&argv[i][0], "-", 1) == 0) {
      flags_count++;
    
      if (strncmp(argv[i], "-n", 2) == 0 || strncmp(argv[i], "-i", 2) == 0) {
        if (strncmp(argv[i], "-n", 2) == 0) {
          number = 1;
        } else {
          ignore = 1;
        }
      } else {
        printf("Error: %s is not a valid flag.\n", argv[i]);
      }
    }
  }

  return flags_count;
}


/*
 * Handles error if there is no enough args
 * (at least three args, including program name, but excluding
 * flags) to process.
 * Exits with failure mode.
 */
void check_args(int argc, int flags_count) {
  if (argc - flags_count < 3) {
    fprintf(stderr, "Too little args! Exiting...\n");
    exit(EXIT_FAILURE);
  }
}


/*
 * USAGE: ./gasp [OPTIONS] PATTERN FILE...
 *
 *
 * [OPTIONS]:
 *  -i: ignores case
 *  -n: includes line numbers in matches found
 *  
 *  Note:
 *   Flags must be given as 2rd and/or 3rd args.
 *   Invalid flags are regarded as flags, and will
 *   print out an error message.
 *
 *  Example: ./gasp -u -i -n hello file1
 *   In this case, since `-u` is an invalid flag,
 *   `-n` will become the pattern
 *   (but NOT the flag since it is not in 2rd/3rd position),
 *   and hello and file1 are regarded as the filenames.
 *   Note that -i flag will STILL be raised.
 *
 * PATTERN:
 *  targeted pattern substring
 *  MAXCHAR is 100 including null terminator.
 *
 * FILE:
 *  At least one file must be given.
 *  throws error otherwise.
 *  If any of the file has error loading,
 *  exit with failure mode.
 *  Otherwise, prints out all the matched lines
 *  (with line numbers if -n flag is raised)
 *  from each file to the stdout
 */
int main(int argc, char *argv[]) {
  int flags_count = 0;
  check_args(argc, flags_count);  // makes sure at least 3 args exist

  flags_count = count_flags(argc, argv);

  check_args(argc, flags_count);

  char pattern[PATTERN_LIMIT];

  // offset by 1 for program name
  int pattern_index = 1 + flags_count;

  // fill pattern with null char
  memset(pattern, '\0', sizeof(pattern));

  // copy 99 chars and
  // leaves 1 char for null terminator
  strncpy(pattern, argv[pattern_index], PATTERN_LIMIT - 1);

  // pattern is transformed to all lowercase
  // if ignore flag is raised
  check_ignore(pattern);   

  print_matched_lines(argc, argv, pattern_index, pattern);

  return EXIT_SUCCESS;
}

