#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Number of input arguments must be 3!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f_word = fopen(argv[1], "r");
  if (f_word == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = readWord(f_word);
  //  printWords(cats);

  if (fclose(f_word) != 0) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[2], "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  substituteAndPrint(f, cats);

  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  freeCats(cats);

  return 0;
}
