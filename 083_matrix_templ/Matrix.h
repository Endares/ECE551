#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  // constructor
  Matrix() : numRows(0), numColumns(0), rows(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = std::vector<std::vector<T> >(numRows);
    for (int i = 0; i < numRows; ++i) {
      rows[i] = std::vector<T>(numColumns);
      // an vector of numColumns elements of T type
    }
  }

  // copy constructor
  // Matrix is a class template, need to have <T>.
  // So that when specialized, the compiler can know its type
  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}

  // destructor: vector has its own destructor
  ~Matrix() {}

  // operator[]
  // need to have both const and non-const version so as to be called on const/non-const Matrix
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && (size_t)index < rows.size());
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && (size_t)index < rows.size());
    return rows[index];
  }

  // assignment operator
  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows =
          rhs.rows;  // vector<T> and nested vector<T> all have their own assignment operator.
    }
    return *this;
  }

  // operator+
  // function type cant' be Matrix<T> &, or res will be a local variable to be deallocted upon return.
  Matrix<T> operator+(const Matrix<T> & rhs) {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix<T> res(numRows, numColumns);
    // Matrix<T> res = Matrix<T>(numRows, numColumns);
    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numColumns; ++j) {
        (res.rows[i])[j] = (this->rows[i])[j] + (rhs.rows[i])[j];
      }
    }
    return res;
  }

  // operator==
  bool operator==(const Matrix<T> & rhs) {
    return numRows == rhs.numRows && numColumns == rhs.numColumns && rows == rhs.rows;
  }

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & vec) {
  s << "{";
  // vector.size() has a type of size_t
  for (size_t i = 0; i < vec.size(); ++i) {
    if (i == vec.size() - 1) {
      s << vec[i];
    }
    else {
      s << vec[i] << ", ";
    }
  }
  s << "}";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
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

#endif
