#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  int reuse = 0;  // 0-allow reuse; 1-no reuse
  if (argc == 3) {
    reuse = 0;
  }
  else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
    reuse = 1;
  }
  else {
    fprintf(stderr, "Invalid arguments number or input format!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f_word = fopen(argv[reuse + 1], "r");
  if (f_word == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = readWord(f_word);
  // printWords(cats);

  if (fclose(f_word) != 0) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[reuse + 2], "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (reuse == 0) {
    substituteAndPrint(f, cats);
  }
  else {
    substituteAndPrint_2(f, cats, 1);
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  freeCats(cats);

  return 0;
}
