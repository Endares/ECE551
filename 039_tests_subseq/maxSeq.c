#include <math.h>
#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t tempLen = 0, maxLen = 0;
  for (size_t i = 1; i < n; ++i) {
    if (array[i] > array[i - 1]) {
      ++tempLen;
    }
    else {
      tempLen = 1;
    }
    if (tempLen > maxLen)
      maxLen = tempLen;
  }
  return maxLen;
}
