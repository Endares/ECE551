#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->arrayLen = 0;
  counts->unknownCnt = 0;
  counts->countsArray = NULL;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    ++(c->unknownCnt);
  }
  else {
    int index = 0;
    for (; index < c->arrayLen; ++index) {
      if (strcmp(name, c->countsArray[index]->str) == 0) {
        ++(c->countsArray[index]->cnt);
        break;
      }
    }
    // this name is new in c
    if (index == c->arrayLen) {
      one_count_t * curr = malloc(sizeof(*curr));
      curr->cnt = 1;
      curr->str = strdup(name);

      ++(c->arrayLen);  // prefix ++ has higher precedence than -> (precedence: prefix ++ > -> > suffix ++)

      one_count_t ** temp = realloc(c->countsArray, c->arrayLen * sizeof(*temp));
      if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(c->countsArray);
        exit(EXIT_FAILURE);
      }
      c->countsArray = temp;
      c->countsArray[index] = curr;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  // a FILE * type is already passed in as parameter, no need to do fopen() here
  for (int i = 0; i < c->arrayLen; ++i) {
    fprintf(outFile, "%s: %d\n", c->countsArray[i]->str, c->countsArray[i]->cnt);
  }
  if (c->unknownCnt != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknownCnt);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->arrayLen; ++i) {
    free(c->countsArray[i]->str);
    free(c->countsArray[i]);
  }
  free(c->countsArray);
  free(c);
}
