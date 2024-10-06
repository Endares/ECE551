#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readSortPrintData(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    char ** temp = realloc(lines, (i + 1) * sizeof(*lines));
    if (temp == NULL) {
      fprintf(stderr, "Memory allocation error\n");
      free(lines);
      exit(EXIT_FAILURE);
    }
    lines = temp;
    // lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    ++i;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; ++j) {
    printf("%s", lines[j]);  // getline() 's string has a '\n' before '\0'
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f;
  if (argc == 1) {
    f = stdin;
    readSortPrintData(f);
    if (fclose(f) != 0) {
      fprintf(stderr, "Error closing file: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  else {
    for (int i = 1; i < argc; ++i) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      readSortPrintData(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "Error closing file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
