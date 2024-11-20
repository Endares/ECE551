#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

// wrapped around binarySearchForZero function, to check its invoking times
void check(Function<int, int> * f,  // function f(x) whose zero point is to be found
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  // max invoking times
  unsigned n = (low <= high) ? std::log2(high - low) + 1 : 1;
  // wrapping function's instance, check invoking time
  CountedIntFn countedFn(n, f, mesg);
  // check search result
  int res = binarySearchForZero(&countedFn, low, high);
  if (res != expected_ans) {
    std::cerr << "expected invokes: " << expected_ans << ", but actually has: " << res
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

// f(x) = x - 2
class Test_func : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 2; }
};

int main(void) {
  Test_func f;  // f(x) = x - 2: zero point is 2
  // binary search the zero point for f(x) = x - 2, [-1000, -2) : approach -3
  check(&f, -1000, -2, -3, "all negitive\n");
  check(&f, 1000, 20000, 1000, "all positive\n");
  check(&f, -1000, 20000, 2, "include 0\n");
  //check(&f, 10000, -2000, 10000, "low > high\n");
  check(&f, -100, 2, 1, "[neg, 2)\n");
  check(&f, 2, 10000, 2, "[2, pos)\n");
  check(&f, 0, 8191, 2, "[0, pos)\n");
  check(&f, -9999, 0, -1, "[neg, 0)\n");
  return 0;
}
