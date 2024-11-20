#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low < high) {
    int mid = (low + high) / 2;
    int x = f->invoke(mid);
    if (x == 0) {
      return mid;
    }
    else if (x < 0) {
      low = mid + 1;
    }
    else {
      high = mid;
    }
  }
  return low;
}
