#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans);

int main() {
  // 10.
  run_check(3, 3, 27);
  // 11.
  run_check(-1, 1, -1);
  run_check(2, 5, 32);
  // 1.
  run_check(0, 0, 1);
  // 2.
  run_check(0, 2, 0);
  // 3.
  run_check(3, 0, 1);
  // 4,
  run_check(5, 2, 25);
  return 0;
}

// helper function
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned res = power(x, y);
  if (res != expected_ans) {
    printf("wrong answer! %d power %d should be %d, but you have %d\n",
           x,
           y,
           expected_ans,
           res);

    exit(EXIT_FAILURE);
  }
  else {
    printf("correct answer! %d power %d should be %d, and you have %d\n",
           x,
           y,
           expected_ans,
           res);
  }
}
