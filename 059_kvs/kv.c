#include "kv.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Remember to free the kvpair and strdup() afterwards*/
kvpair_t * stringToPair(const char * s) {
  kvpair_t * kvp = malloc(sizeof(*kvp));
  if (kvp == NULL) {
    fprintf(stderr, "Malloc failure in function stringToPair.\n");
    exit(EXIT_FAILURE);
  }
  // make a copy of string literal s, so we can modify it.
  // strdup() is also dynamic alloctaion. We need to free it afterwards.
  char * temp = strdup(s);
  kvp->key = temp;

  // "Delete" the '\n' of each string by truncate with '\0'
  char * findNewlineSign = strchr(temp, '\n');
  if (findNewlineSign != NULL) {
    *findNewlineSign = '\0';
  }

  char * findEqualSign = strchr(temp, '=');  // find the first pos of '=' in s

  if (findEqualSign != NULL) {
    // truncate the first part --- key
    *findEqualSign = '\0';

    // get the second part --- value
    kvp->value = findEqualSign + 1;
  }
  else {
    fprintf(stderr, "No equal sign found in the string: %s\n", s);
    exit(EXIT_FAILURE);
  }
  return kvp;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  int index = 0;
  char * curr = NULL;
  size_t linecap = 0;
  kvpair_t ** pairArray = NULL;

  while (getline(&curr, &linecap, f) >= 0) {
    // realloc space for pairArray. temp is used here only for realloc failure detection, dealing with heap leak if realloc fails.
    kvpair_t ** temp = realloc(pairArray, (index + 1) * sizeof(*temp));
    if (temp == NULL) {
      fprintf(stderr, "Memory allocation error\n");
      free(pairArray);
      exit(EXIT_FAILURE);
    }
    pairArray = temp;
    // store the string as a kvpair into pairArray
    pairArray[index] = stringToPair(curr);
    ++index;
    // curr is no longer needed here, it's a string, not a kvpair we want.
    // as long as we have used stringToPair(), so we can cover it in the next turn of the loop
    // curr = NULL;  // if we want to use another space of curr in the next turn, we should free it every turn in the loop.
  }
  free(curr);                 // the last curr is for EOF, it's trash
  kvarray->arrayLen = index;  // not index + 1 !!!
  kvarray->pairArray = pairArray;

  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->arrayLen; ++i) {
    // strdup() is used to create kay and value, it's dynamic alloctaion. So we need to free it here
    // Be cautious not to free twice! Only key is the starting point of allocation
    free(pairs->pairArray[i]->key);
    //free(pairs->pairArray[i]->value);
    free(pairs->pairArray[i]);  // free(void *), so we need pairArray[i]'s address.
  }
  free(pairs->pairArray);  // don't forget!
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->arrayLen; ++i) {
    printf("key = '%s' value = '%s'\n",
           pairs->pairArray[i]->key,
           pairs->pairArray[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->arrayLen; ++i) {
    // str1 == str2 refers to the pointer equivalence. we need to use strcmp() for content comparation
    if (strcmp(key, pairs->pairArray[i]->key) == 0) {
      return pairs->pairArray[i]->value;
    }
  }
  return NULL;
}
