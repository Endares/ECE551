#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

// abstract class with all methods abstract
class Expression {
 public:
  // abstract method
  virtual std::string toString() const = 0;
  // base class for subtype polymorphism must have virtual destructor
  virtual ~Expression() {}
};

// e.g. 9, -7, -9, +4
class NumExpression : public Expression {
 protected:  // need to be accessed by
  long op1;  // trivial type, no need to delete in destructor.

 public:
  // constructor
  NumExpression(long num) : op1(num) {}
  // override
  std::string toString() const {
    std::stringstream ss;
    ss << op1;
    return ss.str();  // str(): turns ss into a string, including '-' prefix
  }
  // Negative numbers will have "-" prefix.
};

// expr with 2 operands
class BinaryExpression : public Expression {
 protected:
  Expression *expr1, *expr2;  // operands
  char opr;

 public:
  // constructor
  BinaryExpression(Expression * lhs, Expression * rhs, char operand) :
      expr1(lhs), expr2(rhs), opr(operand) {}
  // override
  std::string toString() const {
    std::string res;
    res = "(" + expr1->toString() + std::string(opr, 1) + expr2->toString() + ")";
    return res;
  }

  virtual ~BinaryExpression() {
    delete expr1;
    delete expr2;
    // opr is trivial type
  }
};

// which must be a subclass of Expression
class PlusExpression : public BinaryExpression {
 public:
  // constructor
  PlusExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '+') {}
  // no fields of this class its own, no need to write destructor.
};
