#include <stdio.h>
#include <stdlib.h>

int caseNumber = 0;
size_t maxSeq(int * array, size_t n);
void run_check(int * array, size_t n, size_t expected_ans);
int main(void) {
  int array1[] = {1, 1, 1, 1};
  run_check(array1, 4, 1);
  // array2
  run_check(NULL, 0, 0);
  int array3[] = {3, 2, 1};
  run_check(array3, 3, 1);
  int array4[] = {-2, -1, -3};
  run_check(array4, 3, 2);
  int array5[] = {1};
  run_check(array5, 1, 1);
  int array6[] = {1, 3, 5, 1, 2, 3, 6};
  run_check(array6, 7, 4);
  int array7[] = {-8, -9, -10, -2, -1, 1};
  run_check(array7, 6, 4);
  exit(EXIT_SUCCESS);
  return 0;
}

// helper function
void run_check(int * array, size_t n, size_t expected_ans) {
  size_t res = maxSeq(array, n);
  ++caseNumber;
  printf("Case number %d: \n", caseNumber);
  if (res != expected_ans) {
    printf(
        "Wrong answer! The answer should be %zu, but you have %zu\n", expected_ans, res);
    exit(EXIT_FAILURE);
  }
  else {
    printf("Correct answer!\n");
    //exit(EXIT_SUCCESS);
  }
}
