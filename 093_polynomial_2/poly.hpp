#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cassert>
#include <complex>
#include <cstdlib>
#include <iostream>
#include <vector>
template<typename NumT>
class Polynomial {
 private:
  size_t poly_size;
  std::vector<NumT> factors;

 public:
  // Default construct the polynomial to be "0" (i.e., 0*x^0)
  Polynomial() : poly_size(1), factors(1, 0) {}
  Polynomial(size_t n) : poly_size(n), factors(n, 0) {}
  // copy constructor
  Polynomial(const Polynomial & rhs) : poly_size(rhs.poly_size), factors(rhs.factors) {}
  // destructor
  ~Polynomial(){};

  // Add this Polynomial to rhs, and return the resulting polynomial
  Polynomial operator+(const Polynomial & rhs) const {
    Polynomial res(std::max(poly_size, rhs.poly_size));
    for (size_t i = 0; i < res.poly_size; ++i) {
      res.factors[i] =
          (i >= poly_size ? 0 : factors[i]) + (i >= rhs.poly_size ? 0 : rhs.factors[i]);
    }
    return res;
  }
  // Return the negation of this Polynomial.
  Polynomial operator-() const {
    Polynomial res(*this);
    for (size_t i = 0; i < poly_size; ++i) {
      res.factors[i] = -factors[i];
    }
    return res;
  }
  // Subtract rhs from this Polynomial and return the result.
  Polynomial operator-(const Polynomial & rhs) const {
    Polynomial res(std::max(poly_size, rhs.poly_size));
    for (size_t i = 0; i < res.poly_size; ++i) {
      res.factors[i] =
          (i >= poly_size ? 0 : factors[i]) - (i >= rhs.poly_size ? 0 : rhs.factors[i]);
    }
    return res;
  }

  // Multiply this Polynomial by a scalar and return the result
  Polynomial operator*(const NumT & n) const {
    Polynomial res(*this);
    for (size_t i = 0; i < poly_size; ++i) {
      res.factors[i] = n * factors[i];
    }
    return res;
  }
  // Multiply this Polynomial by rhs, and return the result
  Polynomial operator*(const Polynomial & rhs) const {
    Polynomial res(poly_size + rhs.poly_size - 1);
    for (size_t i = 0; i < poly_size; ++i) {
      for (size_t j = 0; j < rhs.poly_size; ++j) {
        res.factors[i + j] += factors[i] * rhs.factors[j];
      }
    }
    return res;
  }

  bool operator==(const Polynomial & rhs) const {
    for (size_t i = 0; i < std::max(poly_size, rhs.poly_size); ++i) {
      if ((i >= poly_size ? 0 : factors[i]) !=
          (i >= rhs.poly_size ? 0 : rhs.factors[i])) {  // e.g. 0*x^1 + 0*x^0 == 0*x^0
        return false;
      }
    }
    return true;
  }
  bool operator!=(const Polynomial & rhs) const { return !operator==(rhs); }

  Polynomial & operator+=(const Polynomial & rhs) {
    Polynomial temp(*this);
    poly_size = std::max(poly_size, rhs.poly_size);
    factors.resize(poly_size, 0);
    for (size_t i = 0; i < poly_size; ++i) {
      factors[i] = (i >= temp.poly_size ? 0 : temp.factors[i]) +
                   (i >= rhs.poly_size ? 0 : rhs.factors[i]);
    }

    return *this;
  }
  Polynomial & operator-=(const Polynomial & rhs) {
    Polynomial temp(*this);
    poly_size = std::max(poly_size, rhs.poly_size);
    factors.resize(poly_size, 0);
    for (size_t i = 0; i < poly_size; ++i) {
      factors[i] = (i >= temp.poly_size ? 0 : temp.factors[i]) -
                   (i >= rhs.poly_size ? 0 : rhs.factors[i]);
    }

    return *this;
  }
  Polynomial & operator*=(const Polynomial & rhs) {
    Polynomial temp(*this);
    poly_size = temp.poly_size + rhs.poly_size - 1;
    factors.assign(poly_size, 0);
    for (size_t i = 0; i < temp.poly_size; ++i) {
      for (size_t j = 0; j < rhs.poly_size; ++j) {
        factors[i + j] += temp.factors[i] * rhs.factors[j];
      }
    }

    return *this;
  }
  Polynomial & operator*=(const NumT & rhs) {
    for (size_t i = 0; i < poly_size; ++i) {
      this->factors[i] *= rhs;
    }
    return *this;
  }

  // Add (c*x^p) to this Polynomial, updating its value.
  void addTerm(const NumT & c, unsigned p) {
    if (poly_size <= p) {
      for (unsigned i = (unsigned)poly_size; i < p; ++i) {
        factors.push_back(0);
      }
      factors.push_back(c);
      poly_size = p + 1;
    }
    else {
      factors[p] += c;
    }
  }

  // evaluates the Polynomial at the given value of "x"
  NumT eval(const NumT & x) const {
    NumT res = NumT(0);
    for (size_t i = 0; i < poly_size; ++i) {
      res += factors[i] * pow(x, i);
    }
    return res;
  }

  // takes the derivative of this Polynomial, resulting in another Polynomial
  Polynomial derivative() const {
    Polynomial res((poly_size > 1 ? poly_size - 1 : 0));
    for (size_t i = 0; i < res.poly_size; ++i) {
      res.factors[i] = factors[i + 1] * NumT(i + 1);
    }
    return res;
  }

  NumT operator()(const NumT & x) const { return eval(x); }

  template<typename N>
  friend std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p);
};

template<typename N>
std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p) {
  bool isZero = true;
  if (p.poly_size == 0) {
    os << "0";
    return os;
  }

  for (int i = static_cast<int>(p.poly_size) - 1; i >= 0; --i) {
    if (p.factors[i] != N(0)) {  // make sure it works for all types
      isZero = false;
      break;
    }
  }
  if (isZero) {
    os << "0";
    return os;
  }
  std::string split = "";
  for (int i = static_cast<int>(p.poly_size) - 1; i >= 0; --i) {
    if (p.factors[i] != N(0)) {
      os << split << p.factors[i] << "*x^" << i;
      split = " + ";
    }
  }
  return os;
}
