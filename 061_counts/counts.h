#ifndef __COUNTS_H__
#define __COUNTS_H__

#include <stdio.h>

// for a particular string str, the times we encoutered it so far is cnt
struct _one_count_t {
  //DEFINE ME
  char * str;
  int cnt;
};
typedef struct _one_count_t one_count_t;

// an array of ptrs to one_count_t, with size arrayLen
struct _counts_t {
  //DEFINE ME
  int arrayLen;
  one_count_t ** countsArray;
  int unknownCnt;  // count for unknown names
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
