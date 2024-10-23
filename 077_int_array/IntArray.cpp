#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  data = NULL;
  numElements = 0;
}
IntArray::IntArray(int n) {
  data = new int[n];
  numElements = n;
}

// copy constructor
IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = new int[numElements];
  for (int i = 0; i < numElements; ++i) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  // check for self-assignment
  if (&rhs != this) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < numElements; ++i) {
      temp[i] = rhs.data[i];
    }
    delete[] data;

    data = temp;
    numElements = rhs.numElements;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  // Checks if the index is in bounds (use assert)
  assert(index >= 0 && index < numElements);
  const int & res = data[index];
  return res;
}
int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  int & res = data[index];
  return res;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this == &rhs) {
    return true;
  }
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; ++i) {
    if (rhs.data[i] != data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.numElements; ++i) {
    s << rhs.data[i];
    if (i < rhs.numElements - 1) {
      s << ", ";
    }
  }
  s << "}\n";
  return s;
}
