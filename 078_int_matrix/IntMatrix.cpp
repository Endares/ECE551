#include "IntMatrix.h"

IntMatrix::IntMatrix() {
  numRows = 0;
  numColumns = 0;
}
IntMatrix::IntMatrix(int r, int c) {
  numRows = r;
  numColumns = c;
  rows = new IntArray *[r];  // rows: an array of IntArray *
  for (int i = 0; i < r; ++i) {
    rows[i] = new IntArray(c);
  }
}
/* copy constructor: construct a new IntMatrix object using copying
   so there isn't anything originally, no need to delete anything
*/
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  //copy these two fields first, or this->numRows would remain unitialized
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;

  // copy using IntArray's copy constructor
  rows = new IntArray *[numRows];
  for (int i = 0; i < rhs.numRows; ++i) {
    rows[i] = new IntArray(rhs[i]);
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; ++i) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    // delete old data
    if (numColumns != 0) {
      for (int i = 0; i < numRows; ++i) {
        delete rows[i];
      }
      delete[] rows;  // if numColumns == 0, rows == NULL
    }

    // copy
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray *[numRows];
    for (int i = 0; i < numRows; ++i) {
      rows[i] = new IntArray(*rhs.rows[i]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];  // return type will be cast to const
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  // same object
  if (this == &rhs) {
    return true;
  }
  if (this->numRows != rhs.numRows || this->numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; ++i) {
    if (*(rows[i]) != *(rhs.rows[i])) {  // calling IntArray's operator!=
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numRows == rhs.numRows && this->numColumns == rhs.numColumns);

  IntMatrix res(numRows, numColumns);
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numColumns; ++j) {
      int a = (*rows[i])[j];
      int b = (*(rhs.rows[i]))[j];
      (*(res.rows[i]))[j] = a + b;
    }
  }
  return res;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); ++i) {
    if (i == rhs.getRows() - 1) {
      s << rhs[i];
    }
    else {
      s << rhs[i] << ",\n";
    }
  }
  s << " ]";
  return s;
}
