#include <ctype.h>
#include <stdio.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

// abstract class with all methods abstract
class Expression {
 public:
  // abstract method
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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

  long evaluate() const { return op1; }
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
    std::stringstream ss;
    ss << "(" << expr1->toString() << " " << opr << " " << expr2->toString() << ")";
    return ss.str();
  }

  long evaluate() const {
    switch (opr) {
      case '+':
        return expr1->evaluate() + expr2->evaluate();
        break;
      case '-':
        return expr1->evaluate() - expr2->evaluate();
        break;
      case '*':
        return expr1->evaluate() * expr2->evaluate();
        break;
      case '/':
        if (expr2->evaluate() == 0) {
          std::cout << "Divisor cannot be zero!" << std::endl;
          exit(EXIT_FAILURE);
        }
        return expr1->evaluate() / expr2->evaluate();
        break;
      default:
        std::cout << "Invalid operator: " << opr << "!" << std::endl;
        exit(EXIT_FAILURE);
    }
  }

  virtual ~BinaryExpression() {
    delete expr1;
    delete expr2;
    // opr is trivial type
  }
};

class PlusExpression : public BinaryExpression {
 public:
  // constructor
  PlusExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '+') {}
  // no fields of this class its own, no need to write destructor.
};

class MinusExpression : public BinaryExpression {
 public:
  // constructor
  MinusExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '-') {}
  // no fields of this class its own, no need to write destructor.
};

class TimesExpression : public BinaryExpression {
 public:
  // constructor
  TimesExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '*') {}
  // no fields of this class its own, no need to write destructor.
};

class DivExpression : public BinaryExpression {
 public:
  // constructor
  DivExpression(Expression * lhs, Expression * rhs) : BinaryExpression(lhs, rhs, '/') {}
  // no fields of this class its own, no need to write destructor.
};
