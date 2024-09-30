#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(
        stderr, "Error: wrong number of arguments.\n Usage: %s, <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char matrix[10][10];
  int c;

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j <= 10; ++j) {  // matrix[][10] for '\n' of each line
      c = fgetc(f);
      if (c == EOF) {
        fprintf(stderr, "Invalid input: too less values int the matrix.\n");
        exit(EXIT_FAILURE);
      }
      if (j == 10) {
        if (c != '\n') {
          fprintf(stderr, "Invalid input: missing newline character at line %d\n", i);
          exit(EXIT_FAILURE);
        }
      }
      else {
        if (c == '\n') {
          fprintf(stderr, "Invalid input: newline character within a line\n");
          exit(EXIT_FAILURE);
        }
        matrix[j][9 - i] = c;
      }
    }
  }
  if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "Invalid input: too many values in the matrix.\n");
    exit(EXIT_FAILURE);
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
  return 0;
}
