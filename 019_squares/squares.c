#include <stdbool.h>
void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = (size1 > (x_offset + size2)) ? size1 : x_offset + size2;
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = (size1 > (y_offset + size2)) ? size1 : y_offset + size2;
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; ++y) {
    //count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; ++x) {
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND
      bool f1 = (x >= x_offset) && (x < x_offset + size2);
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      bool f2 = (y == y_offset) || (y == y_offset + size2 - 1);
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      bool f3 = (y >= y_offset) && (y < y_offset + size2);
      //     x is equal to either x_offset OR x_offset + size2 -1)
      bool f4 = (x == x_offset) || (x == x_offset + size2 - 1);
      // if so, print a *
      if ((f1 && f2) || (f3 && f4)) {
        printf("*");
      }
      //if not,
      else {
        if (((x < size1) && ((y == 0) || (y == size1 - 1))) ||
            ((y < size1) && ((x == 0) || (x == size1 - 1)))) {
          printf("#");
        }
        else {
          printf(" ");
        }
      }
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #
    }
    printf("\n");
  }
  //else print a space
  //when you finish counting x from 0 to w,
  //print a newline
}
