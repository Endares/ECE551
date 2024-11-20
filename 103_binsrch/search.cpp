#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  // base case: low >= high - 1, only <= 1 elements, directly return
  while (low < high - 1) {
    int mid = (low + high) / 2;
    int x = f->invoke(mid);
    if (x == 0) {
      return mid;
    }
    else if (x < 0) {
      low = mid;
    }
    else {
      high = mid;
    }
  }
  return low;
}
